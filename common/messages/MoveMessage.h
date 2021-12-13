#ifndef QUANTUM_CHESS_MOVEMESSAGE_H
#define QUANTUM_CHESS_MOVEMESSAGE_H

#include <MovementCommand.h>
#include "Message.h"

class MoveMessage : public Message {
protected:
    std::unique_ptr<MovementCommand> movement;
    int charToInt(const char &i);
public:
    MoveMessage(int id = -1);
    MoveMessage(const std::string &message, int id = -1);
    virtual void apply(Board& board, Chat&) const override;
};

#endif //QUANTUM_CHESS_MOVEMESSAGE_H
