#include <iostream>
#include "ChatMessage.h"
#include "Protocol.h"
#include <string.h>
#include <arpa/inet.h>

/***********************
    Metodos publicos
************************/

ChatMessage::ChatMessage(int id) : Message(id), msg_len(0) {
    this->type = CHAT_CHAR;
}

ChatMessage::ChatMessage(const std::string &message, int id) : Message(message, id){
    this->type = CHAT_CHAR;
}

const std::string ChatMessage::getMessage() const {
    return _message;
}

const std::string ChatMessage::getEncodedMessage() const {
    unsigned short int len = htons(_message.size());
    char len_arr[2];
    memcpy(len_arr, &len, 2);
    std::string encoded_message;
    encoded_message.push_back(len_arr[0]);
    encoded_message.push_back(len_arr[1]);
    encoded_message += _message;

    return encoded_message;
}

void ChatMessage::apply(Board&) const {
    if (this->id == -1)
        std::cout << "This user added a message to chat. Message: " 
                    << _message << std::endl;
    else
        std::cout << "User " << this->id << " added a message to chat. Message: " 
                    << _message << std::endl;
}

void ChatMessage::apply(Board&, 
                        BlockingQueue<std::shared_ptr<std::string>> &chatQueue) const {
    std::string msg;
    if (this->id == -1) msg = "You: ";
    else msg = "User " + std::to_string(this->id) + ": ";

    msg += this->_message;

    chatQueue.produce(std::make_shared<std::string>(msg));
}

int ChatMessage::getBytesToRead() {
    if (msg_len == 0)
        return sizeof(unsigned short int);
    if (this->_message.size() > 0)
        return 0;
    return msg_len;
}

void ChatMessage::decode(std::vector<char> &buf) {
    if (msg_len == 0) {
        unsigned short int name_len_be;
        memcpy(&name_len_be, buf.data(), sizeof(unsigned short int));
        msg_len = ntohs(name_len_be);
    } else {
        this->_message = std::string(buf.data(), msg_len);
    }
}
