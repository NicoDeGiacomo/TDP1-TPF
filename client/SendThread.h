#ifndef _SEND_THREAD_H_
#define _SEND_THREAD_H_

#include "Thread.h"
#include "ServerProxy.h"
#include "BlockingQueue.h"
#include "ServerProxy.h"
#include "Message.h"
#include <atomic>

class SendThread: public Thread {
private:
    ServerProxy &proxy;
    Board &board;
    Chat &chat;
    std::atomic<bool> keep_talking;
    BlockingQueue<std::shared_ptr<Message>> &sendQueue;

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
    SendThread(ServerProxy &proxy, Board &board, Chat &chat, 
                BlockingQueue<std::shared_ptr<Message>> &sendQueue);
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
