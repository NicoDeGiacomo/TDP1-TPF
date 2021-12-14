#include <iostream>
#include "NormalMove.h"

NormalMove::NormalMove(Position &&from, Position &&to) 
                    : MovementCommand({std::move(from), std::move(to)}) {}

void NormalMove::move(Board &board) {
    board.move(this->_positions[0], this->_positions[1]);
}

