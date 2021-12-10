#ifndef PLAYER_NAME_MESSAGE_H
#define PLAYER_NAME_MESSAGE_H

#include "VariableLenghtMessage.h"

class PlayerNameMessage : public VariableLenghtMessage {
public:
    PlayerNameMessage(int id = -1);
    PlayerNameMessage(const std::string &message, int id = -1);
    virtual void apply(Board&) const override;
    virtual void apply(Board&, Chat &chat) const override;
};


#endif // PLAYER_NAME_MESSAGE_H
