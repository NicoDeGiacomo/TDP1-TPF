//
// Created by ale on 16/11/21.
//

#include "NormalMoveMessage.h"
#include "movements/MovementCommand.h"
#include <iostream>
#include <NormalMove.h>
#include <SplitMove.h>
#include <MergeMove.h>
#include "Protocol.h"

NormalMoveMessage::NormalMoveMessage(const std::string &message, int id) : MoveMessage(message, id) {
    std::cout << "constructor of NormalMoveMessage class" << std::endl;
    
    Position from(this->charToInt(message.at(0)),
                    this->charToInt(message.at(1)));
    Position to(this->charToInt(message.at(2)),
                this->charToInt(message.at(3)));
    std::cout << "finish constructor" << std::endl;
    this->movement = std::make_unique<NormalMove>(std::move(from),
                                                    std::move(to));
    this->type = NORMAL_MOVE_CHAR;
}

NormalMoveMessage::NormalMoveMessage(Position& from, Position& to) {
    this->_message.clear();
    this->_message += from.getString();
    this->_message += to.getString();
    
    this->movement = std::make_unique<NormalMove>(std::move(from),
                                                    std::move(to));
    this->type = NORMAL_MOVE_CHAR;
}

/*NormalMoveMessage::NormalMoveMessage(const std::string &message) : MoveMessage() {
    this->movement = std::make_unique<NormalMove>(std::move(from),
                                                  std::move(to));*/
//}


