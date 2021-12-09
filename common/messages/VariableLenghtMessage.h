#ifndef _VARIABLE_LENGHT_MESSAGE_H_
#define _VARIABLE_LENGHT_MESSAGE_H_

#include <Message.h>
#include <string>

class VariableLenghtMessage : public Message {
protected:
    VariableLenghtMessage(int id = -1);
    VariableLenghtMessage(const std::string &message, int id = -1);
public:
    const std::string getEncodedMessage() const override;
    virtual int getBytesToRead() override;
    virtual void decode(std::vector<char> &buf) override;
};

#endif
