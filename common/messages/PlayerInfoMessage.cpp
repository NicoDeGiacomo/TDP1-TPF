#include "PlayerInfoMessage.h"

PlayerInfoMessage::PlayerInfoMessage(const std::string &message, int id) 
                                    : Message(message, id) {}

const std::string& PlayerInfoMessage::getMessage() const {
    
}


void PlayerInfoMessage::apply(Board&) const {}