#ifndef QUANTUM_CHESS_PLAYER_H
#define QUANTUM_CHESS_PLAYER_H


#include <Socket.h>
#include "BlockingQueue.h"
#include "messages/Message.h"
#include "ClientProxy.h"
#include "RecvThread.h"

class Player {
private:
    ClientProxy proxy;
    BlockingQueue <std::shared_ptr<Message>> &queueOfReceived;
    RecvThread recvThread;
public:
    Player(ClientProxy &client,
           BlockingQueue<std::shared_ptr<Message>> &queue);

    /*
     *  Constructor por copia
     */
    Player(const Player&) = delete;
    /*
     *  Asignacion por copia
     */
    Player& operator=(const Player&) = delete;

    void send(const std::shared_ptr<Message>& message) const;

    void startReceivingMessages();

    bool isDead() const;

    int getId();

    void join();
};


#endif //QUANTUM_CHESS_PLAYER_H
