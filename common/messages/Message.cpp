//
// Created by ale on 13/11/21.
//

#include <iostream>
#include "Message.h"

const std::string& Message::getMessage() const {
    std::cout << "get message from Message class" << std::endl;
    return this->_message;
}

const std::string& Message::getId() const {
    std::cout << "get id from Message class" << std::endl;
    return this->idOfCreator;
}

Message::Message(const std::string& message, const std::string& id) : idOfCreator(id), _message(message) {
    std::cout << "constructor of Message class" << std::endl;
}
