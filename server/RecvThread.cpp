#include "RecvThread.h"
#include "Socket.h"
#include "Message.h"
#include "Protocol.h"
#include <iostream>

/***********************
    Metodos protegidos
************************/

void RecvThread::run() {
    while (keep_talking) {
        std::shared_ptr<Message> message = proxy.recv();
        queueOfReceived.produce(std::move(message));
    }
}

/***********************
    Metodos publicos
************************/

RecvThread::RecvThread(ClientProxy &proxy, 
                       BlockingQueue<std::shared_ptr<Message>> &queue)
                       : proxy(proxy),
                       queueOfReceived(queue),
                       keep_talking(true) {}

void RecvThread::stop() {
    this->keep_talking = false;
    // this->proxy.close_connection();
}
