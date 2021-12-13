#include "NormalMoveMessage.h"
#include "movements/MovementCommand.h"
#include <iostream>
#include <NormalMove.h>
#include <SplitMove.h>
#include <MergeMove.h>
#include "Protocol.h"

/***********************
    Metodos privados
************************/

std::unique_ptr<MovementCommand> NormalMoveMessage::makeMovement(const char *buf) {
    Position from(this->charToInt(buf[0]),
                    this->charToInt(buf[1]));
    Position to(this->charToInt(buf[2]),
                this->charToInt(buf[3]));
    return std::make_unique<NormalMove>(std::move(from),
                                        std::move(to));
}

/***********************
    Metodos publicos
************************/

NormalMoveMessage::NormalMoveMessage(int id) : MoveMessage(id) {
    this->type = NORMAL_MOVE_CHAR;
    this->_msg_len = 4;
}

NormalMoveMessage::NormalMoveMessage(Position& from, Position& to) {
    this->_message.clear();
    this->_message += from.getString();
    this->_message += to.getString();
    
    this->movement = std::make_unique<NormalMove>(std::move(from),
                                                    std::move(to));
    this->type = NORMAL_MOVE_CHAR;
    this->_msg_len = 4;
}

void NormalMoveMessage::decode(std::vector<char> &buf) {
    this->movement = makeMovement(buf.data());
    this->_message = std::string(buf.data(), _msg_len);
}
