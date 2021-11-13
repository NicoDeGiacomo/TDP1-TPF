//
// Created by ale on 13/11/21.
//

#include "Message.h"

const std::string& Message::getMessage() const {
    return this->_message;
}

void Message::setMessage(const std::string &message) {
    this->_message = message;
}

Message::Message(const std::string &message) {
    this->setMessage(message);
}
