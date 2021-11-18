//
// Created by ale on 18/11/21.
//

#include <iostream>
#include "NormalMove.h"

NormalMove::NormalMove(Position &&from, Position &&to) : MovementCommand({std::move(from), std::move(to)}) {
    std::cout << "constructor of normal move" << std::endl;
}

void NormalMove::move(Board &board) {
    std::cout << "do normal move" << std::endl;
    board.move(this->_positions[0], this->_positions[1]);
}

