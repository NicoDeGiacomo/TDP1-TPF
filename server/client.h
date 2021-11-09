//
// Created by ale on 9/11/2021.
//

#ifndef QUANTUM_CHESS_CLIENT_H
#define QUANTUM_CHESS_CLIENT_H
#include <string>
#include "Socket.h"

class Client {
private:
    std::string name;
public:
    void notify();
};


#endif //QUANTUM_CHESS_CLIENT_H
