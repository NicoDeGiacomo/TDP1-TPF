#include "MergeMove.h"
#include <iostream>

MergeMove::MergeMove(Position &&from1, Position &&from2, Position &&to) : MovementCommand({std::move(from1),
                                                                                         std::move(from2),
                                                                                         std::move(to)}) {}

void MergeMove::move(Board &board) {
    board.merge(this->_positions[0], this->_positions[1], this->_positions[2]);
}