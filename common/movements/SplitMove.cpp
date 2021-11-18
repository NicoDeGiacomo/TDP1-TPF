//
// Created by ale on 18/11/21.
//

#include "SplitMove.h"
#include <iostream>

SplitMove::SplitMove(Position &&from, Position &&to1, Position &&to2) : MovementCommand({std::move(from),
                                                                                         std::move(to1),
                                                                                         std::move(to2)}) {
    std::cout << "constructor of split move" << std::endl;
}

void SplitMove::move(Board &board) {
    std::cout << "do split move" << std::endl;
    board.split(this->_positions[0], this->_positions[1], this->_positions[2]);
}