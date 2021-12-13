//
// Created by ale on 16/11/21.
//

#ifndef QUANTUM_CHESS_SELECTMESSAGE_H
#define QUANTUM_CHESS_SELECTMESSAGE_H

#include "Message.h"

class SelectMessage : public Message {
public:
    SelectMessage(int id = -1);
    virtual void apply(Board&, Chat&) const override;
};


#endif //QUANTUM_CHESS_SELECTMESSAGE_H
