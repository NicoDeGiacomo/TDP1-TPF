#ifndef PLAYER_TYPE_MESSAGE_H
#define PLAYER_TYPE_MESSAGE_H

#include "Message.h"

class PlayerTypeMessage : public Message {
public:
    PlayerTypeMessage(int id = -1);
    PlayerTypeMessage(char type);
    virtual void apply(Board&, Chat&) const override;
};

#endif //PLAYER_TYPE_MESSAGE_H
