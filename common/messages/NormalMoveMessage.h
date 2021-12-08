#ifndef QUANTUM_CHESS_NORMAL_MOVE_MESSAGE_H
#define QUANTUM_CHESS_NORMAL_MOVE_MESSAGE_H

#include <MovementCommand.h>
#include "MoveMessage.h"


class NormalMoveMessage : public MoveMessage {
public:
    NormalMoveMessage(int id = -1);
    NormalMoveMessage(Position& from, Position& to);
    std::unique_ptr<MovementCommand> makeMovement(const char *buf);
    void decode(std::vector<char> &buf);
};


#endif //QUANTUM_CHESS_MOVEMESSAGE_H
