#ifndef SEED_MESSAGE_H
#define SEED_MESSAGE_H

#include "Message.h"

class SeedMessage : public Message {
public:
    SeedMessage(int id = -1);
    SeedMessage(unsigned int seed);
    virtual void apply(Board&) const override;
    virtual void apply(Board&, Chat&) const override;
};

#endif // SEED_TYPE_MESSAGE_H
