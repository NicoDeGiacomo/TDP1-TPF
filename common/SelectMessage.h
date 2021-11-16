//
// Created by ale on 16/11/21.
//

#ifndef QUANTUM_CHESS_SELECTMESSAGE_H
#define QUANTUM_CHESS_SELECTMESSAGE_H

#include "Message.h"

class SelectMessage : public Message {
public:
    SelectMessage(const std::string &message);
    const std::string& getMessage() const override;
};


#endif //QUANTUM_CHESS_SELECTMESSAGE_H
