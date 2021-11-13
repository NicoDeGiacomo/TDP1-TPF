//
// Created by ale on 13/11/21.
//

#ifndef QUANTUM_CHESS_MESSAGE_H
#define QUANTUM_CHESS_MESSAGE_H


#include <string>

class Message {
private:
    std::string _message;
public:
    explicit Message(const std::string& message);
    const std::string& getMessage() const;
    void setMessage(const std::string& message);
};


#endif //QUANTUM_CHESS_MESSAGE_H
