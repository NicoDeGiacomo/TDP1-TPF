//
// Created by ale on 12/11/21.
//

#ifndef QUANTUM_CHESS_PLAYER_H
#define QUANTUM_CHESS_PLAYER_H


#include <Socket.h>
#include <thread>
#include "BlockingQueue.h"
#include "messages/Message.h"

class Player {
private:
    Socket socket;
    BlockingQueue <std::shared_ptr<Message>> *queueOfReceived;
    std::thread receiverThread;
    std::string id;
public:
    Player();

    void send(const std::shared_ptr<Message>& message) const;

    bool isVacant() const;

    void startReceivingMessages();
    void initPlayer(Socket &&socket, BlockingQueue<std::shared_ptr<Message>> *queue);
    Player(Socket&& socket, BlockingQueue<std::shared_ptr<Message>> *queue);

    void runReceiverThread();

    void join();

    ~Player();
};


#endif //QUANTUM_CHESS_PLAYER_H
