//
// Created by ale on 12/11/21.
//

#ifndef QUANTUM_CHESS_PLAYER_H
#define QUANTUM_CHESS_PLAYER_H


#include <Socket.h>
#include <thread>
#include "BlockingQueue.h"

class Player {
private:
    Socket socket;
    BlockingQueue <std::string> *queueOfReceived;
    std::thread receiverThread;
public:
    Player();
    void receive(char* buffer, int size);

    void send(const char *message, int size);

    bool isVacant();

    void startReceivingMessages();

    void initPlayer(Socket &&socket, BlockingQueue<std::string> *queue);

    Player(Socket&& socket, BlockingQueue<std::string> *queue);

    void runReceiverThread();

    void join();
};


#endif //QUANTUM_CHESS_PLAYER_H
