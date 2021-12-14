#ifndef QUANTUM_CHESS_SPLIT_MOVE_MESSAGE_H
#define QUANTUM_CHESS_SPLIT_MOVE_MESSAGE_H

#include <MovementCommand.h>
#include "MoveMessage.h"

class SplitMoveMessage : public MoveMessage {
public:
    SplitMoveMessage(int id = -1);
    SplitMoveMessage(Position& from, Position& to_1, Position& to_2);
    std::unique_ptr<MovementCommand> makeMovement(const char *buf);
    void decode(std::vector<char> &buf);
};


#endif //QUANTUM_CHESS_SPLIT_MOVE_MESSAGE_H
