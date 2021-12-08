#include "PlayerNameMessage.h"
#include "Protocol.h"
#include <arpa/inet.h>
#include <string.h>

/***********************
    Metodos publicos
************************/

PlayerNameMessage::PlayerNameMessage(int id) : Message(id), msg_len(0) {
    this->type = PLAYER_NAME_CHAR;
}

PlayerNameMessage::PlayerNameMessage(const std::string &message, int id) : Message(message, id){
    this->type = PLAYER_NAME_CHAR;
}

const std::string PlayerNameMessage::getMessage() const {
    return _message;
}

const std::string PlayerNameMessage::getEncodedMessage() const {
    unsigned short int len = htons(_message.size());
    char len_arr[2];
    memcpy(len_arr, &len, 2);
    std::string encoded_message;
    encoded_message.push_back(len_arr[0]);
    encoded_message.push_back(len_arr[1]);
    encoded_message += _message;

    return encoded_message;
}

void PlayerNameMessage::apply(Board&) const {
    
}

void PlayerNameMessage::apply(Board&, Chat &chat) const {
    chat.addUser(this->id, this->_message);
}

int PlayerNameMessage::getBytesToRead() {
    if (msg_len == 0)
        return sizeof(unsigned short int);
    if (this->_message.size() > 0)
        return 0;
    return msg_len;
}

void PlayerNameMessage::decode(std::vector<char> &buf) {
    if (msg_len == 0) {
        unsigned short int name_len_be;
        memcpy(&name_len_be, buf.data(), sizeof(unsigned short int));
        msg_len = ntohs(name_len_be);
    } else {
        this->_message = std::string(buf.data(), msg_len);
    }
}

