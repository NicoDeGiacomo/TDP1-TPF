#include "PlayerTypeMessage.h"
#include "Protocol.h"
#include <iostream>

/***********************
    Metodos publicos
************************/

PlayerTypeMessage::PlayerTypeMessage(int id) : Message(id) {
    this->type = PLAYER_TYPE_CHAR;
    this->_msg_len = 1;
}

PlayerTypeMessage::PlayerTypeMessage(char type) {
    this->type = PLAYER_TYPE_CHAR;
    this->_msg_len = 1;
    this->_message = type;
}

void PlayerTypeMessage::apply(Board&) const {
    throw std::runtime_error("This method should not be called");
}

void PlayerTypeMessage::apply(Board&, Chat &) const {
    throw std::runtime_error("This method should not be called");
}
