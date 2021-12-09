#include <iostream>
#include "Message.h"

/***********************
    Metodos publicos
************************/

Message::Message(int id) : _msg_len(0), id(id) {}

Message::Message(const std::string& message, int id)
                    : _message(message), 
                      _msg_len(message.size()),
                      id(id) {}

const std::string Message::getMessage() const {
    return this->_message;
}

const std::string Message::getEncodedMessage() const {
    return this->_message;
}

int Message::getId() const {
    return this->id;
}

char Message::getType() const {
    return this->type;
}

int Message::getBytesToRead() {
    if (_message.size() == 0)
        return _msg_len;
    return 0;
}

void Message::decode(std::vector<char> &buf) {
    this->_message = std::string(buf.data(), _msg_len);
}

