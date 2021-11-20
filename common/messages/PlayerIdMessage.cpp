#include "PlayerIdMessage.h"

PlayerIdMessage::PlayerIdMessage(int id) : Message(), id(id) {}

int PlayerIdMessage::getId() {
    return id;
}

void PlayerIdMessage::apply(Board &board) const {
    board.printBoard();
    
}

const std::string &PlayerIdMessage::getMessage() const {
    return Message::getMessage();
}
