#ifndef QUANTUM_CHESS_MERGE_MOVE_MESSAGE_H
#define QUANTUM_CHESS_MERGE_MOVE_MESSAGE_H

#include <MovementCommand.h>
#include "MoveMessage.h"

class MergeMoveMessage : public MoveMessage {
public:
    MergeMoveMessage(int id = -1);
    MergeMoveMessage(Position& from_1, Position& from_2, Position& to);
    std::unique_ptr<MovementCommand> makeMovement(const char *buf);
    void decode(std::vector<char> &buf);
};


#endif //QUANTUM_CHESS_MOVEMESSAGE_H
