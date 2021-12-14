#ifndef QUANTUM_CHESS_SPLITMOVE_H
#define QUANTUM_CHESS_SPLITMOVE_H

#include <Position.h>
#include <Board.h>
#include "MovementCommand.h"

class SplitMove : public MovementCommand {
public:
    SplitMove(Position&& from, Position&& to1, Position&& to2);
    void move(Board& board) override;
};


#endif //QUANTUM_CHESS_SPLITMOVE_H
