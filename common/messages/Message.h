//
// Created by ale on 13/11/21.
//

#ifndef QUANTUM_CHESS_MESSAGE_H
#define QUANTUM_CHESS_MESSAGE_H


#include <string>
#include <Board.h>
#include <BlockingQueue.h>

class Message {
protected:
    bool server;
    // std::string idOfCreator;
    std::string _message;
    char type;
    int id;
public:
    Message();
    Message(const std::string& message, int id);
    virtual const std::string getMessage() const;
    int getId() const;
    char getType() const;
    virtual void apply(Board&) const {}
    virtual void apply(Board&, BlockingQueue<std::shared_ptr<std::string>>&) const {}
    // virtual apply(Board, Chat)
        // board.move(pos1, pos2)
        // chat
    // recv --> apply --> propagas
    // recv --> apply --> return error
    virtual ~Message() = default;
};


#endif //QUANTUM_CHESS_MESSAGE_H
