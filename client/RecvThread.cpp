#include "RecvThread.h"
#include "Message.h"
#include "Protocol.h"
#include "StageMode.h"
#include <iostream>


/***********************
    Metodos protegidos
************************/

void RecvThread::run() {
    StageMode::log("Running RecvThread");
    
    while (keep_talking) {
        try {
            std::shared_ptr<Message> message = proxy.recv();
            queue.produce(std::move(message));
        } catch(const ClosedSocketException &e) {
            this->stop();
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
    this->queue.close();
}
