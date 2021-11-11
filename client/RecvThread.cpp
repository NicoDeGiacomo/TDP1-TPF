#include "RecvThread.h"

/***********************
    Metodos protegidos
************************/

void RecvThread::run() {
    Action action;
    while (this->keep_talking) {
        action = proxy.recv();
        this->queue.produce(action);
    }
}

/***********************
    Metodos publicos
************************/

RecvThread::RecvThread(BlockingQueue<Action> &queue) : queue(queue), keep_talking(true) {}

void RecvThread::stop() {
    this->keep_talking = false;
    this->proxy.close_connection();
}
