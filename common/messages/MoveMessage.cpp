#include "MoveMessage.h"
#include "movements/MovementCommand.h"
#include <iostream>
#include <NormalMove.h>
#include <SplitMove.h>
#include <MergeMove.h>

/***********************
    Metodos publicos
************************/

MoveMessage::MoveMessage(int id) : Message(id) {}

MoveMessage::MoveMessage(const std::string &message, int id) : Message(message, id) {
    this->movement.reset();
}

int MoveMessage::charToInt(const char &i) {
    return i - '0';
}

void MoveMessage::apply(Board &board) const {
    this->movement->move(board);
}

void MoveMessage::apply(Board& board, Chat&) const {
    this->apply(board);
}
