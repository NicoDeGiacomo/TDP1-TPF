//
// Created by ale on 9/11/2021.
//

#ifndef QUANTUM_CHESS_CLIENT_H
#define QUANTUM_CHESS_CLIENT_H


#include <Board.h>
#include "Socket.h"
#include "ServerProxy.h"
#include "MainGameScreen.h"

class Client {
private:
    ServerProxy proxy;
    Board _board;
    BlockingQueue<std::shared_ptr<std::string>> chatQueue;
    MainGameScreen mainGameScreen;
    int id;
    char playerType;
    std::string name;
    BlockingQueue<std::shared_ptr<Message>> recvQueue;
    BlockingQueue<std::shared_ptr<Message>> sendQueue;
public:
    Client(const char *host, const char *service);

    void run();

    BlockingQueue<std::shared_ptr<Message>> *getQueue();
};


#endif //QUANTUM_CHESS_CLIENT_H
