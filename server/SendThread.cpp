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
            message->apply(board);
            for (auto &spectator : spectators) {
                spectator.send(message);
            }
            //this if itsVacant is just not to break things
            //better send logic needs to be added
            if (!playerWhite.isVacant())
                playerWhite.send(message);
            if (!playerBlack.isVacant())
                playerBlack.send(message);
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
                       Player &playerWhite,
                       Player &playerBlack,
                       std::list<Player> &spectators,
                       Board &board)
                       : queueOfReceived(queueOfReceived),
                       playerWhite(playerWhite),
                       playerBlack(playerBlack),
                       spectators(spectators),
                       board(board),
                       keep_talking(true) {}

void SendThread::stop() {
    /*this->keep_talking = false;
    this->proxy.close_connection();*/
}
