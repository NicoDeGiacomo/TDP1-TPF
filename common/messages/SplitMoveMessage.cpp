//
// Created by ale on 16/11/21.
//

#include "SplitMoveMessage.h"
#include "movements/MovementCommand.h"
#include "Protocol.h"
#include <iostream>
#include <NormalMove.h>
#include <SplitMove.h>
#include <MergeMove.h>

SplitMoveMessage::SplitMoveMessage(const std::string &message, int id) : MoveMessage(message, id) {
    std::cout << "constructor of SplitMoveMessage class" << std::endl;
 
    Position from(this->charToInt(message.at(0)),
                        this->charToInt(message.at(1)));
    Position to1(this->charToInt(message.at(2)),
                this->charToInt(message.at(3)));
    Position to2(this->charToInt(message.at(4)),
                this->charToInt(message.at(5)));
    this->movement = std::make_unique<SplitMove>(std::move(from),
                                                std::move(to1),
                                                std::move(to2));
    this->type = SPLIT_MOVE_CHAR;
}
