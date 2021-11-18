//
// Created by ale on 16/11/21.
//

#include <iostream>
#include "ChatMessage.h"

//TODO: here i should decode the message
const std::string &ChatMessage::getMessage() const {
    std::cout << "get message from ChatMessage class" << std::endl;
    return this->_message;
}

const std::string &ChatMessage::getId() const {
    std::cout << "get id from ChatMessage class" << std::endl;
    return Message::getId();
}

//TODO: here i should encode the message
ChatMessage::ChatMessage(const std::string &message, const std::string& id) : Message(message, id){
    this->_message = message;
    std::cout << "constructor of ChatMessage class" << std::endl;
}
