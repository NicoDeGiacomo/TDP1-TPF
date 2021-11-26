//
// Created by ale on 9/11/2021.
//

#include <string>
#include <iostream>
#include <Socket.h>
#include <thread>
#include <Message.h>
#include <Protocol.h>
#include "Client.h"
#include "RecvThread.h"
#include "SendThread.h"

void Client::run() {
    RecvThread recvThread(proxy, recvQueue);
    SendThread sendThread(proxy, _board, id, sendQueue);
    recvThread.start();
    sendThread.start();
    // mainGameScreen()
    bool gameFinished = false;

    while (!gameFinished) {
        mainGameScreen.processUserInput(gameFinished);
        mainGameScreen.refreshScreen();
        bool moreMessagesToProcess = true;
        while(moreMessagesToProcess) {
            std::shared_ptr<Message> msg_ptr = recvQueue.popIfNotEmpty();

            if (!msg_ptr) {
                moreMessagesToProcess = false;
                continue;
            }
            try {
                msg_ptr->apply(_board);
            } catch (const std::exception &e) {
                std::cerr << "Exception caught in client: '"
                          << e.what() << "'" << std::endl;
            } catch (...) {
                std::cerr << "Unknown error caught in client.\n";
            }
        }

        // sleep para fps, maybe hay una mejor forma de hacerlo
        SDL_Delay(1);
    }
    recvThread.stop();
    recvThread.join();
    sendThread.stop();
    sendThread.join();
}
/*Client::Client movePieze(Position&& from, Position&& to){

}*/

BlockingQueue<std::shared_ptr<Message>>* Client::getQueue(){
    return &sendQueue;
}

Client::Client(const char *host, const char *service, Board& board) : mainGameScreen(board, &sendQueue), proxy(), _board(board) {

    //std::cin.ignore();
    proxy.connect(host, service);
    id = -1;
    // std::cout << "Choose your name: ";
    // std::getline(std::cin, name);
    // int room_id;
    // std::cout << "Choose a room: ";
    // std::cin >> room_id;
}

