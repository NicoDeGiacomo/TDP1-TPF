//
// Created by ale on 13/11/21.
//

#ifndef QUANTUM_CHESS_MESSAGE_H
#define QUANTUM_CHESS_MESSAGE_H


#include <string>

class Message {
  bool server;
  String from; // pepito
  String id;
protected:
    std::string _message;
public:
    explicit Message(const std::string& message);
    virtual const std::string& getMessage() const;
    virtual apply(Board, Chat)
        // board.move(pos1, pos2)
        // chat
    // recv --> apply --> propagas
    // recv --> apply --> return error
    virtual ~Message() {}
};


#endif //QUANTUM_CHESS_MESSAGE_H
