#ifndef QUANTUM_CHESS_MESSAGE_H
#define QUANTUM_CHESS_MESSAGE_H

#include <string>
#include <Board.h>
#include <BlockingQueue.h>

class Board;

class Message {
protected:
    bool server;
    // std::string idOfCreator;
    std::string _message;
    int _msg_len;
    char type;
    int id;
    Message(int id = -1);
    Message(const std::string& message, int id = -1);
public:
    virtual const std::string getMessage() const;
    virtual const std::string getEncodedMessage() const;
    // virtual const std::string getEncodedMessage(char id) const;
    int getId() const;
    char getType() const;
    virtual void apply(Board&) const {}
    virtual void apply(Board&, BlockingQueue<std::shared_ptr<std::string>>&) const {}
    virtual int getBytesToRead();
    virtual void decode(std::vector<char> &);
    // virtual apply(Board, Chat)
        // board.move(pos1, pos2)
        // chat
    // recv --> apply --> propagas
    // recv --> apply --> return error
    virtual ~Message() = default;
};


#endif //QUANTUM_CHESS_MESSAGE_H
