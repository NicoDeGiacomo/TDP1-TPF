//
// Created by ale on 18/11/21.
//

#include "MergeMove.h"
#include <iostream>

MergeMove::MergeMove(Position &&from1, Position &&from2, Position &&to) : MovementCommand({std::move(from1),
                                                                                         std::move(from2),
                                                                                         std::move(to)}) {
    std::cout << "constructor of merge move" << std::endl;
}

void MergeMove::move(Board &board) {
    std::cout << "do merge move" << std::endl;
    board.merge(this->_positions[0], this->_positions[1], this->_positions[2]);
}