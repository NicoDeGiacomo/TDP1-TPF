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
    // ServerProxy proxy;
    // BlockingQueue<std::shared_ptr<Message>> &queue;
    ServerProxy &proxy;
    Board &board;
    int id;
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
    SendThread(ServerProxy &proxy, Board &board, int id);
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
