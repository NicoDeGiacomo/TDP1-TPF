#ifndef ROOM_ID_MESSAGE_H
#define ROOM_ID_MESSAGE_H

#include "VariableLenghtMessage.h"

class RoomIdMessage : public VariableLenghtMessage {
public:
    RoomIdMessage(int id = -1);
    RoomIdMessage(const std::string &message, int id = -1);
    virtual void apply(Board&) const override;
    virtual void apply(Board&, Chat &) const override;
};


#endif // PLAYER_NAME_MESSAGE_H
