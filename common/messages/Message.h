#ifndef QUANTUM_CHESS_MESSAGE_H
#define QUANTUM_CHESS_MESSAGE_H

#include <string>
#include <Board.h>
#include <Chat.h>

class Board;

class Message {
protected:
    bool server;
    std::string _message;
    int _msg_len;
    char type;
    int id;
    Message(int id = -1);
    Message(const std::string& message, int id = -1);
public:
    int getId() const;
    char getType() const;
    virtual const std::string getMessage() const;
    virtual const std::string getEncodedMessage() const;
    virtual int getBytesToRead();
    virtual void decode(std::vector<char> &);
    virtual void apply(Board&) const {}
    virtual void apply(Board&, Chat&) const {}
    virtual ~Message() = default;
};


#endif //QUANTUM_CHESS_MESSAGE_H
