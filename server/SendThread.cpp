#include "SendThread.h"
#include "Message.h"
#include <iostream>

/***********************
    Metodos protegidos
************************/

void SendThread::run() {
    while (keep_talking) {
        try {
            std::shared_ptr<Message> message = queueOfReceived.top();
            queueOfReceived.pop();
            message->apply(board, chat);
            for (auto &player : players) {
                player.send(message);
            }
        } catch (const ClosedSocketException& e){
            std::cout << e.what() << std::endl;
            this->stop();
        } catch(const ClosedQueueException &e) {
            std::cout << e.what() << std::endl;
            this->stop();
        }
    }
}

/***********************
    Metodos publicos
************************/

SendThread::SendThread(BlockingQueue <std::shared_ptr<Message>> &queueOfReceived, 
                       std::list<Player> &players,
                       Board &board,
                       Chat &chat)
                       : queueOfReceived(queueOfReceived),
                       players(players),
                       board(board),
                       chat(chat),
                       keep_talking(true) {}

void SendThread::stop() {
    this->keep_talking = false;
    this->queueOfReceived.close();
}
