//
// Created by ale on 18/11/21.
//

#ifndef QUANTUM_CHESS_MERGEMOVE_H
#define QUANTUM_CHESS_MERGEMOVE_H

#include <Position.h>
#include <Board.h>
#include "MovementCommand.h"

class MergeMove : public MovementCommand {
public:
    MergeMove(Position&& from1, Position&& from2, Position&& to);
    void move(Board& board) override;
};


#endif //QUANTUM_CHESS_MERGEMOVE_H
