//
// Created by ale on 16/11/21.
//

#ifndef QUANTUM_CHESS_MERGE_MOVE_MESSAGE_H
#define QUANTUM_CHESS_MERGE_MOVE_MESSAGE_H

#include <MovementCommand.h>
#include "MoveMessage.h"

class MergeMoveMessage : public MoveMessage {
public:
    MergeMoveMessage(const std::string &message, int id);
};


#endif //QUANTUM_CHESS_MOVEMESSAGE_H
