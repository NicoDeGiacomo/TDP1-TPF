#include "SplitMoveMessage.h"
#include "movements/MovementCommand.h"
#include "Protocol.h"
#include <iostream>
#include <NormalMove.h>
#include <SplitMove.h>
#include <MergeMove.h>

/***********************
    Metodos privados
************************/

std::unique_ptr<MovementCommand> SplitMoveMessage::makeMovement(const char *buf) {
    Position from(this->charToInt(buf[0]),
                        this->charToInt(buf[1]));
    Position to1(this->charToInt(buf[2]),
                this->charToInt(buf[3]));
    Position to2(this->charToInt(buf[4]),
                this->charToInt(buf[5]));
    return std::make_unique<SplitMove>(std::move(from),
                                       std::move(to1),
                                       std::move(to2));
}

/***********************
    Metodos publicos
************************/

SplitMoveMessage::SplitMoveMessage(int id) : MoveMessage(id) {
    this->type = SPLIT_MOVE_CHAR;
    this->_msg_len = 6;
}

SplitMoveMessage::SplitMoveMessage(Position& from, Position& to_1, Position& to_2) {
    this->_message.clear();
    this->_message += from.getString();
    this->_message += to_1.getString();
    this->_message += to_2.getString();

    this->movement = std::make_unique<SplitMove>(std::move(from),
                                                 std::move(to_1),
                                                 std::move(to_2));
    this->type = SPLIT_MOVE_CHAR;
    this->_msg_len = 6;
}

void SplitMoveMessage::decode(std::vector<char> &buf) {
    this->movement = makeMovement(buf.data());
    this->_message = std::string(buf.data(), _msg_len);
}
