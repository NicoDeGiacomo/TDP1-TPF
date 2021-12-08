#ifndef PLAYER_NAME_MESSAGE_H
#define PLAYER_NAME_MESSAGE_H

#include "Message.h"

class PlayerNameMessage : public Message {
private:
    unsigned short int msg_len;
public:
    PlayerNameMessage(int id = -1);
    PlayerNameMessage(const std::string &message, int id = -1);
    const std::string getMessage() const override;
    const std::string getEncodedMessage() const override;
    virtual void apply(Board&) const override;
    void apply(Board&, Chat &chat) const override;
    virtual int getBytesToRead() override;
    virtual void decode(std::vector<char> &buf) override;
};


#endif // PLAYER_NAME_MESSAGE_H
