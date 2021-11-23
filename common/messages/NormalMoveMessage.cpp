//
// Created by ale on 16/11/21.
//

#include "NormalMoveMessage.h"
#include "movements/MovementCommand.h"
#include <iostream>
#include <NormalMove.h>
#include <SplitMove.h>
#include <MergeMove.h>

NormalMoveMessage::NormalMoveMessage(const std::string &message, int id) : MoveMessage(message, id) {
    std::cout << "constructor of NormalMoveMessage class" << std::endl;
    
    Position from(this->charToInt(message.at(1)),
                    this->charToInt(message.at(2)));
    Position to(this->charToInt(message.at(3)),
                this->charToInt(message.at(4)));
    std::cout << "finish constructor" << std::endl;
    this->movement = std::make_unique<NormalMove>(std::move(from),
                                                    std::move(to));
}

/*NormalMoveMessage::NormalMoveMessage(const std::string &message) : MoveMessage() {
    this->movement = std::make_unique<NormalMove>(std::move(from),
                                                  std::move(to));*/
//}
