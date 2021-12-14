#include "SplitMove.h"
#include <iostream>

SplitMove::SplitMove(Position &&from, Position &&to1, Position &&to2) : MovementCommand({std::move(from),
                                                                                         std::move(to1),
                                                                                         std::move(to2)}) {}

void SplitMove::move(Board &board) {
    board.split(this->_positions[0], this->_positions[1], this->_positions[2]);
}