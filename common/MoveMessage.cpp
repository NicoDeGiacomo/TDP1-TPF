//
// Created by ale on 16/11/21.
//

#include "MoveMessage.h"
#include <iostream>
//TODO: here i should decode the message
const std::string &MoveMessage::getMessage() const {
    std::cout << "get message from MoveMessage class" << std::endl;
    return this->_message;
}
//TODO: here i should encode the message
MoveMessage::MoveMessage(const std::string &message) : Message(message){
    std::cout << "constructor of MoveMessage class" << std::endl;
}