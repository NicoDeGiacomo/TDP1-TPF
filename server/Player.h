//
// Created by ale on 12/11/21.
//

#ifndef QUANTUM_CHESS_PLAYER_H
#define QUANTUM_CHESS_PLAYER_H


#include <Socket.h>
// #include <thread>
#include "BlockingQueue.h"
#include "messages/Message.h"
#include "ClientProxy.h"
#include "RecvThread.h"

class Player {
private:
    // Socket socket;
    ClientProxy proxy;
    BlockingQueue <std::shared_ptr<Message>> &queueOfReceived;
    // std::thread receiverThread;
    RecvThread recvThread;
    int id;
public:
    Player(BlockingQueue <std::shared_ptr<Message>> &queueOfReceived);

    Player(Socket &socket,
           BlockingQueue<std::shared_ptr<Message>> &queue, 
           int id, 
           char type,
           unsigned int seed);

    void initPlayer(Socket &socket, int id, char type, unsigned int seed);

    void send(const std::shared_ptr<Message>& message) const;

    bool isVacant() const;

    void startReceivingMessages();

    int getId();

    void join();

    ~Player();
};


#endif //QUANTUM_CHESS_PLAYER_H
