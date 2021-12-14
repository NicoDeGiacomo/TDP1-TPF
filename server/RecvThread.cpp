#include "RecvThread.h"
#include "Socket.h"
#include "Message.h"
#include <iostream>

/***********************
    Metodos protegidos
************************/

void RecvThread::run() {
    while (keep_talking) {
        try {
            std::shared_ptr<Message> message = proxy.recv();
            queueOfReceived.produce(std::move(message));
        } catch (ClosedSocketException& e) {
            std::cout << "Socket closed. Closing RecvThread" << std::endl;
            this->stop();
        } catch(const ClosedQueueException &e) {
            std::cout << "Closed queue. Closing RecvThread" << std::endl;
            this->stop();
        }
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
    std::cout << "Closing RecvThread\n";
    this->keep_talking = false;
    this->proxy.close_connection();
}
