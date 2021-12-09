#ifndef QUANTUM_CHESS_CHATMESSAGE_H
#define QUANTUM_CHESS_CHATMESSAGE_H

#include "VariableLenghtMessage.h"

class ChatMessage : public VariableLenghtMessage {
public:
    ChatMessage(int id = -1);
    ChatMessage(const std::string &message, int id = -1);
    virtual void apply(Board&) const override;
    virtual void apply(Board&, Chat &chat) const override;
};


#endif //QUANTUM_CHESS_CHATMESSAGE_H
