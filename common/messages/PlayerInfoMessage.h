#ifndef QUANTUM_CHESS_PLAYER_INFO_MESSAGE_H
#define QUANTUM_CHESS_PLAYER_INFO_MESSAGE_H

#include "Message.h"

class PlayerInfoMessage : public Message {
public:
    PlayerInfoMessage(const std::string &message, int id);
    const std::string getMessage() const override;
    // const std::string& getId() const override;
    virtual void apply(Board&) const override;
};


#endif //QUANTUM_CHESS_CHATMESSAGE_H
