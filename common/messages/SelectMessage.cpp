#include "SelectMessage.h"
#include "Protocol.h"
#include <iostream>

/***********************
    Metodos publicos
************************/

SelectMessage::SelectMessage(int id) : Message(id) {
    this->type = SELECT_CHAR;
    this->_msg_len = 2;
}

const std::string SelectMessage::getMessage() const {
    return this->_message;
}

void SelectMessage::apply(Board&, Chat&) const {}
