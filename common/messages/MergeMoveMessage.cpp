//
// Created by ale on 16/11/21.
//

#include "MergeMoveMessage.h"
#include "movements/MovementCommand.h"
#include <iostream>
#include <NormalMove.h>
#include <SplitMove.h>
#include <MergeMove.h>
#include "Protocol.h"

MergeMoveMessage::MergeMoveMessage(const std::string &message, int id) : MoveMessage(message, id) {
    std::cout << "constructor of MergeMoveMessage class" << std::endl;
    
    Position from1(this->charToInt(message.at(0)),
                    this->charToInt(message.at(1)));
    Position from2(this->charToInt(message.at(2)),
                this->charToInt(message.at(3)));
    Position to(this->charToInt(message.at(4)),
                    this->charToInt(message.at(5)));
    this->movement = std::make_unique<MergeMove>(std::move(from1),
                                                    std::move(from2),
                                                    std::move(to));
    this->type = MERGE_MOVE_CHAR;
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
}

