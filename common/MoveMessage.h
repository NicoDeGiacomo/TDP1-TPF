//
// Created by ale on 16/11/21.
//

#ifndef QUANTUM_CHESS_MOVEMESSAGE_H
#define QUANTUM_CHESS_MOVEMESSAGE_H

#include "Message.h"

class MoveMessage : public Message {
public:
    MoveMessage(const std::string &message);
    const std::string& getMessage() const override;
};


#endif //QUANTUM_CHESS_MOVEMESSAGE_H
