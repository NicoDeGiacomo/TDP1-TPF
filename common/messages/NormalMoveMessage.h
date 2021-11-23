//
// Created by ale on 16/11/21.
//

#ifndef QUANTUM_CHESS_NORMAL_MOVE_MESSAGE_H
#define QUANTUM_CHESS_NORMAL_MOVE_MESSAGE_H

#include <MovementCommand.h>
#include "MoveMessage.h"

class NormalMoveMessage : public MoveMessage {
public:
    NormalMoveMessage(const std::string &message, int id);
};


#endif //QUANTUM_CHESS_MOVEMESSAGE_H
