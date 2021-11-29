//
// Created by ale on 16/11/21.
//

#include "SelectMessage.h"
#include "Protocol.h"
#include <iostream>

//TODO: here i should decode the message
const std::string SelectMessage::getMessage() const {
    std::cout << "get message from SelectMessage class" << std::endl;
    return this->_message;
}

// const std::string &SelectMessage::getId() const {
//     std::cout << "get id from SelectMessage class" << std::endl;
//     //this may not work, idk
//     return Message::getId();
// }

//TODO: here i should encode the message
SelectMessage::SelectMessage(const std::string &message, int id) : Message(message, id){
    this->_message = message;
    std::cout << "constructor of SelectMessage class" << std::endl;
    this->type = SELECT_CHAR;
}

void SelectMessage::apply(Board&, 
                        BlockingQueue<std::shared_ptr<std::string>>&) const {}
