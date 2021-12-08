#ifndef QUANTUM_CHESS_MOVEMESSAGE_H
#define QUANTUM_CHESS_MOVEMESSAGE_H

#include <MovementCommand.h>
#include "Message.h"

class MoveMessage : public Message {
protected:
    std::unique_ptr<MovementCommand> movement;
public:
    MoveMessage(int id = -1);
    MoveMessage(const std::string &message, int id = -1);
    const std::string getMessage() const override;
    virtual void apply(Board& board) const override;
    virtual void apply(Board& board, 
                    BlockingQueue<std::shared_ptr<std::string>>&) const override;
    int charToInt(const char &i);
};


#endif //QUANTUM_CHESS_MOVEMESSAGE_H
