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
    SendThread sendThread(proxy, _board, id, sendQueue, chatQueue);
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
                msg_ptr->apply(_board, chatQueue);
            } catch (const std::exception &e) {
                std::cerr << "Exception caught in client: '"
                          << e.what() << "'" << std::endl;
            } catch (...) {
                std::cerr << "Unknown error caught in client.\n";
            }
        }

        // sleep para fps, maybe hay una mejor forma de hacerlo
        SDL_Delay(1);
        if (_board.isFinished()){
            mainGameScreen.refreshScreen();
            mainGameScreen.endMessage(SPECTATOR_CHAR);
            break; 
        }
    }
    recvThread.stop();
    recvThread.join();
    sendThread.stop();
    sendThread.join();
}

BlockingQueue<std::shared_ptr<Message>>* Client::getQueue(){
    return &sendQueue;
}

Client::Client(const char *host, const char *service, Board& board) 
            : proxy(host, service), _board(board), chatQueue(), mainGameScreen(board, &sendQueue, chatQueue, proxy.getPlayerType()) {

    //std::cin.ignore();
    //proxy.connect(host, service);
    playerType = proxy.getPlayerType();
    id = -1;
    // std::cout << "Choose your name: ";
    // std::getline(std::cin, name);
    // int room_id;
    // std::cout << "Choose a room: ";
    // std::cin >> room_id;
}

