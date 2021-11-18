//
// Created by ale on 18/11/21.
//

#ifndef QUANTUM_CHESS_NORMALMOVE_H
#define QUANTUM_CHESS_NORMALMOVE_H


#include <Position.h>
#include <Board.h>
#include "MovementCommand.h"

class NormalMove : public MovementCommand {
public:
    NormalMove(Position&& from, Position&& to);
    void move(Board& board) override;
};


#endif //QUANTUM_CHESS_NORMALMOVE_H
