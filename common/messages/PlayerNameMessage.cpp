#include "PlayerNameMessage.h"
#include "Protocol.h"
#include <arpa/inet.h>
#include <string.h>

/***********************
    Metodos publicos
************************/

PlayerNameMessage::PlayerNameMessage(int id) : VariableLenghtMessage(id) {
    this->type = PLAYER_NAME_CHAR;
}

PlayerNameMessage::PlayerNameMessage(const std::string &message, int id) 
                                    : VariableLenghtMessage(message, id) {
    this->type = PLAYER_NAME_CHAR;
}

void PlayerNameMessage::apply(Board&, Chat &chat) const {
    chat.addUser(this->id, this->_message);
}
