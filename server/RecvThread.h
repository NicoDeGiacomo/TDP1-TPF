#ifndef _RECV_THREAD_H_
#define _RECV_THREAD_H_

#include "Thread.h"
#include "ClientProxy.h"
#include "BlockingQueue.h"
#include "Message.h"
#include <atomic>

class RecvThread: public Thread {
private:
    ClientProxy &proxy;
    BlockingQueue <std::shared_ptr<Message>> &queueOfReceived;
    std::atomic<bool> keep_talking;

protected:
    /*
     *  La ejecucion de un hilo RecvServer consiste en recibir acciones
     *  a realizar del server y guardarlas en ActionsQueue.
     */
    void run() override;

public:
    /*
     *  Constructor
     */
    RecvThread(ClientProxy &proxy, BlockingQueue<std::shared_ptr<Message>> &queue);
    /*
     *  Constructor por copia
     */
    RecvThread(const RecvThread &other) = delete;
    /*
     *  Constructor por movimiento
     */
    RecvThread(RecvThread &&other);
    /*
     *  Termina la comunicacion con el server
     */
    void stop();
};

#endif
