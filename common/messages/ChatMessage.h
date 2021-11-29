//
// Created by ale on 16/11/21.
//

#ifndef QUANTUM_CHESS_CHATMESSAGE_H
#define QUANTUM_CHESS_CHATMESSAGE_H

#include "Message.h"

class ChatMessage : public Message {
public:
    ChatMessage(const std::string &message, int id);
    const std::string getMessage() const override;
    // const std::string& getId() const override;
    virtual void apply(Board&) const override;
    void apply(Board&, BlockingQueue<std::shared_ptr<std::string>> &chatQueue) const override;
};


#endif //QUANTUM_CHESS_CHATMESSAGE_H
