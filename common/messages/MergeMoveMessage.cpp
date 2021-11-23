//
// Created by ale on 16/11/21.
//

#include "MergeMoveMessage.h"
#include "movements/MovementCommand.h"
#include <iostream>
#include <NormalMove.h>
#include <SplitMove.h>
#include <MergeMove.h>

MergeMoveMessage::MergeMoveMessage(const std::string &message, int id) : MoveMessage(message, id) {
    std::cout << "constructor of MergeMoveMessage class" << std::endl;
    
    Position from1(this->charToInt(message.at(1)),
                    this->charToInt(message.at(2)));
    Position from2(this->charToInt(message.at(3)),
                this->charToInt(message.at(4)));
    Position to(this->charToInt(message.at(5)),
                    this->charToInt(message.at(6)));
    this->movement = std::make_unique<MergeMove>(std::move(from1),
                                                    std::move(from2),
                                                    std::move(to));
}
