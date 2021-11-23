//
// Created by ale on 9/11/2021.
//

#ifndef QUANTUM_CHESS_CLIENT_H
#define QUANTUM_CHESS_CLIENT_H


#include <Board.h>
#include "Socket.h"
#include "BlockingQueue.h"
#include "Message.h"
#include "ServerProxy.h"

class Client {
private:
    ServerProxy proxy;
    Board &_board;
    int id;
    std::string name;
    BlockingQueue<std::shared_ptr<Message>> recvQueue;
    // BlockingQueue<std::shared_ptr<Message>> sendQueue;
public:
    Client(const char *host, const char *service, Board &board);

    void run();

    BlockingQueue<std::shared_ptr<Message>> *getQueue();
};


#endif //QUANTUM_CHESS_CLIENT_H
