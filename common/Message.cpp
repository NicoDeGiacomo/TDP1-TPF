//
// Created by ale on 13/11/21.
//

#include <iostream>
#include "Message.h"

const std::string& Message::getMessage() const {
    std::cout << "get message from ChatMessage class" << std::endl;
    return this->_message;
}

Message::Message(const std::string& message) : _message(message) {
    std::cout << "constructor of Message class" << std::endl;
}
