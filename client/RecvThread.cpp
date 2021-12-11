#include "RecvThread.h"
#include "Message.h"
#include "Protocol.h"
#include <iostream>


/***********************
    Metodos protegidos
************************/

void RecvThread::run() {
    std::cout << "Running RecvThread\n";
    
    while (keep_talking) {
        try {
            std::shared_ptr<Message> message = proxy.recv();
            queue.produce(std::move(message));
        } catch(const std::exception &e) {
            this->stop();
            std::cerr << "Exception caught in RecvThread: '" 
                    << e.what() << "'" << std::endl;
        } catch(...) {
            this->stop();
            std::cerr << "Unknown error caught in RecvThread" << std::endl;
            return;
        }
    }
}

/***********************
    Metodos publicos
************************/

RecvThread::RecvThread(ServerProxy &proxy, BlockingQueue<std::shared_ptr<Message>> &queue) 
                    : proxy(proxy), queue(queue), keep_talking(true) {}

void RecvThread::stop() {
    this->keep_talking = false;
    this->proxy.close_connection();
}
