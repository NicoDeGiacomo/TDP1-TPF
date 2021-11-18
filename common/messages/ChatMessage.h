//
// Created by ale on 16/11/21.
//

#ifndef QUANTUM_CHESS_CHATMESSAGE_H
#define QUANTUM_CHESS_CHATMESSAGE_H

#include "Message.h"

class ChatMessage : public Message {
public:
    ChatMessage(const std::string &message, const std::string& id);
    const std::string& getMessage() const override;
    const std::string& getId() const override;
};


#endif //QUANTUM_CHESS_CHATMESSAGE_H
