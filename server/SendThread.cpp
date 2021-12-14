#include "SendThread.h"
#include "Message.h"
#include <iostream>

/***********************
    Metodos protegidos
************************/

void SendThread::run() {
    while (keep_talking) {
        std::shared_ptr<Message> message = queueOfReceived.top();
        queueOfReceived.pop();
        try {
            message->apply(board, chat);
            for (auto &player : players) {
                player.send(message);
            }
        } catch (ClosedSocketException& e){
            //TODO: for some reason this catch isnt catching, the socket
            //is throwing the error receiving bytes exception instead
            std::cout << e.what() << std::endl;
            return;
        } catch(const std::exception &e) {
            std::cerr << "Exception caught in SendThread: '" 
                    << e.what() << "'" << std::endl;
        }
        // std::cout << "-server just sent: " << std::endl <<
        // message->getMessage() << std::endl;
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
