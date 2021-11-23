//
// Created by ale on 13/11/21.
//

#include <iostream>
#include "Message.h"

const std::string Message::getMessage() const {
    // std::cout << "get message from Message class" << std::endl;
    return this->_message; //n1213 //c05n1213
}

int Message::getId() const {
    // std::cout << "get id from Message class" << std::endl;
    return this->id;
}

Message::Message(const std::string& message, int id) : _message(message), id(id) {
    // std::cout << "constructor of Message class" << std::endl;
}

Message::Message() {

}
