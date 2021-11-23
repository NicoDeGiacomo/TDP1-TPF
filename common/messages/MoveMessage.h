//
// Created by ale on 16/11/21.
//

#ifndef QUANTUM_CHESS_MOVEMESSAGE_H
#define QUANTUM_CHESS_MOVEMESSAGE_H

#include <MovementCommand.h>
#include "Message.h"
#define NORMAL_MOVE 'n'
#define MERGE_MOVE 'm'
#define SPLIT_MOVE 's'
class MoveMessage : public Message {
protected:
    std::unique_ptr<MovementCommand> movement;
public:
    MoveMessage(std::string& message);
    MoveMessage() {};
    MoveMessage(const std::string &message, int id);
    const std::string getMessage() const override;
    // const std::string& getId() const override;
    virtual void apply(Board& board) const override;

    int charToInt(const char &i);
};


#endif //QUANTUM_CHESS_MOVEMESSAGE_H
