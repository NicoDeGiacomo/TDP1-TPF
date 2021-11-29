//
// Created by ale on 16/11/21.
//

#include <iostream>
#include "ChatMessage.h"
#include "Protocol.h"
#include <arpa/inet.h>

//TODO: here i should decode the message
const std::string ChatMessage::getMessage() const {
    // std::cout << "get message from ChatMessage class" << std::endl;
    // char type = CHAT_CHAR;
    // unsigned short int msg_len = _message.length();
    // unsigned short int msg_len_be = htons(msg_len);
    // char msg_owner_id = id;
    
    // std::string msg;
    // msg += type;
    // msg += msg_owner_id;
    // msg += msg_len_be;
    // msg += _message;

    return _message;
}

// const std::string &ChatMessage::getId() const {
//     // std::cout << "get id from ChatMessage class" << std::endl;
//     return Message::getId();
// }

//TODO: here i should encode the message
ChatMessage::ChatMessage(const std::string &message, int id) : Message(message, id){
    // this->_message = message;
    this->type = CHAT_CHAR;
    // std::cout << "constructor of ChatMessage class" << std::endl;
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
    chatQueue.produce(std::make_shared<std::string>(_message));
}
