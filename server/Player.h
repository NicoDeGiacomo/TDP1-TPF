//
// Created by ale on 12/11/21.
//

#ifndef QUANTUM_CHESS_PLAYER_H
#define QUANTUM_CHESS_PLAYER_H


#include <Socket.h>
#include <thread>
#include "BlockingQueue.h"
#include "Message.h"

class Player {
private:
    Socket socket;
    BlockingQueue <std::unique_ptr<Message>> *queueOfReceived;
    std::thread receiverThread;

    //TODO: remove this sender queue, is just for debugging
    BlockingQueue <Message> *_thisSenderQueueIsJustForDebugging;
public:
    Player();

    void send(const Message& message) const;

    bool isVacant() const;

    void startReceivingMessages();
    //TODO: remove this sender queue, is just for debugging
    void initPlayer(Socket &&socket, BlockingQueue<std::unique_ptr<Message>> *queue, BlockingQueue<Message> *thisSenderQueueIsJustForDebugging);
    //TODO: remove this sender queue, is just for debugging
    Player(Socket&& socket, BlockingQueue<std::unique_ptr<Message>> *queue, BlockingQueue<Message> *thisSenderQueueIsJustForDebugging);

    void runReceiverThread();

    void join();

    ~Player();
};


#endif //QUANTUM_CHESS_PLAYER_H
