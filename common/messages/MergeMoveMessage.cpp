#include "MergeMoveMessage.h"
#include "movements/MovementCommand.h"
#include <iostream>
#include <NormalMove.h>
#include <SplitMove.h>
#include <MergeMove.h>
#include "Protocol.h"

/***********************
    Metodos privados
************************/

std::unique_ptr<MovementCommand> MergeMoveMessage::makeMovement(const char *buf) {
    Position from1(this->charToInt(buf[0]),
                    this->charToInt(buf[1]));
    Position from2(this->charToInt(buf[2]),
                this->charToInt(buf[3]));
    Position to(this->charToInt(buf[4]),
                    this->charToInt(buf[5]));
    return std::make_unique<MergeMove>(std::move(from1),
                                       std::move(from2),
                                       std::move(to));
}

/***********************
    Metodos publicos
************************/

MergeMoveMessage::MergeMoveMessage(int id) : MoveMessage(id) {
    this->type = MERGE_MOVE_CHAR;
    this->_msg_len = 6;
}

MergeMoveMessage::MergeMoveMessage(Position& from_1, Position& from_2, Position& to) {
    this->_message.clear();
    this->_message += from_1.getString();
    this->_message += from_2.getString();
    this->_message += to.getString();
    
    this->movement = std::make_unique<MergeMove>(std::move(from_1),
                                                 std::move(from_2),
                                                 std::move(to));
    this->type = MERGE_MOVE_CHAR;
    this->_msg_len = 6;
}

void MergeMoveMessage::decode(std::vector<char> &buf) {
    this->movement = makeMovement(buf.data());
    this->_message = std::string(buf.data(), _msg_len);
}
