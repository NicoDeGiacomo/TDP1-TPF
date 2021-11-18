//
// Created by ale on 13/11/21.
//

#ifndef QUANTUM_CHESS_MESSAGE_H
#define QUANTUM_CHESS_MESSAGE_H


#include <string>
#include <Board.h>

class Message {
protected:
    bool server;
    std::string idOfCreator;
    std::string _message;
public:
    explicit Message(const std::string& message, const std::string& id);
    virtual const std::string& getMessage() const;
    virtual const std::string& getId() const;
    virtual void apply(Board&) const {}
    // virtual apply(Board, Chat)
        // board.move(pos1, pos2)
        // chat
    // recv --> apply --> propagas
    // recv --> apply --> return error
    virtual ~Message() = default;
};


#endif //QUANTUM_CHESS_MESSAGE_H
