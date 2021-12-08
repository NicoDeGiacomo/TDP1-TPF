#include "MoveMessage.h"
#include "movements/MovementCommand.h"
#include <iostream>
#include <NormalMove.h>
#include <SplitMove.h>
#include <MergeMove.h>

/***********************
    Metodos publicos
************************/

MoveMessage::MoveMessage(int id) : Message(id) {};

MoveMessage::MoveMessage(const std::string &message, int id) : Message(message, id) {
    this->movement.reset();
}

const std::string MoveMessage::getMessage() const {
    return this->_message;
}

int MoveMessage::charToInt(const char &i) {
    return i - '0';
}

void MoveMessage::apply(Board &board) const {
    std::cout << "apply move message" << std::endl;
    this->movement->move(board);
}

void MoveMessage::apply(Board& board,
                    BlockingQueue<std::shared_ptr<std::string>>&) const {
    this->apply(board);
}
