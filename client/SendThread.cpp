#include "SendThread.h"

/***********************
    Metodos protegidos
************************/

void SendThread::run() {
    while (this->keep_talking) {
        Action action = this->queue.top();
        proxy.send(action);
        this->queue.pop();
    }
}

/***********************
    Metodos publicos
************************/

SendThread::SendThread(BlockingQueue<Action> &queue) 
                : queue(queue), 
                  keep_talking(true) {}

void SendThread::stop() {
    this->keep_talking = false;
    this->proxy.close_connection();
}
