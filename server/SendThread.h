#ifndef _SEND_THREAD_H_
#define _SEND_THREAD_H_

#include "Thread.h"
#include "ServerProxy.h"
#include "BlockingQueue.h"
#include "Player.h"
#include "Board.h"
#include <list>
#include <atomic>

class SendThread: public Thread {
private:
    BlockingQueue <std::shared_ptr<Message>> &queueOfReceived;
    Player &playerWhite;
    Player &playerBlack;
    std::list<Player> &spectators;
    Board &board;
    std::atomic<bool> keep_talking;

protected:
    /*
     *  La ejecucion de un hilo SendThread consiste en desencolar acciones
     *  de ActionsQueue y enviarlas al server.
     */
    void run() override;

public:
    /*
     *  Constructor
     */
    SendThread(BlockingQueue <std::shared_ptr<Message>> &queueOfReceived,
               Player &playerWhite,
               Player &playerBlack,
               std::list<Player> &spectators,
               Board &board);
    /*
     *  Constructor por copia
     */
    SendThread(const SendThread &other) = delete;
    /*
     *  Constructor por movimiento
     */
    SendThread(SendThread &&other);
    /*
     *  Termina la comunicacion con el server
     */
    void stop();
};

#endif
