#ifndef QUANTUM_CHESS_CHATMESSAGE_H
#define QUANTUM_CHESS_CHATMESSAGE_H

#include "Message.h"

class ChatMessage : public Message {
private:
    unsigned short int msg_len;
public:
    ChatMessage(int id = -1);
    ChatMessage(const std::string &message, int id = -1);
    const std::string getMessage() const override;
    const std::string getEncodedMessage() const override;
    virtual void apply(Board&) const override;
    void apply(Board&, BlockingQueue<std::shared_ptr<std::string>> &chatQueue) const override;
    virtual int getBytesToRead() override;
    virtual void decode(std::vector<char> &buf) override;
};


#endif //QUANTUM_CHESS_CHATMESSAGE_H
