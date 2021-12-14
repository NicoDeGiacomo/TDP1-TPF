#include "RoomIdMessage.h"
#include "Protocol.h"

/***********************
    Metodos publicos
************************/

RoomIdMessage::RoomIdMessage(int id) : VariableLenghtMessage(id) {
    this->type = ROOM_ID_CHAR;
}

RoomIdMessage::RoomIdMessage(const std::string &message, int id) 
                                    : VariableLenghtMessage(message, id) {
    this->type = ROOM_ID_CHAR;
}

void RoomIdMessage::apply(Board&, Chat &) const {
    // throw std::runtime_error("This method should not be called");
}
