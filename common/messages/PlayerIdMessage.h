#ifndef QUANTUM_CHESS_ID_MESSAGE_H
#define QUANTUM_CHESS_ID_MESSAGE_H

#include "Message.h"

class PlayerIdMessage : public Message {
    int id;
public:
    PlayerIdMessage(int id);
    const std::string getMessage() const override;
    // const std::string& getId() const override;
    void apply(Board& board) const override;
    int getId();
};


#endif //QUANTUM_CHESS_ID_MESSAGE_H
