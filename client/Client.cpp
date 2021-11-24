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

    //while (1) {  // este while
        while (1) {
            std::shared_ptr<Message> msg_ptr = recvQueue.top(); // no bloqueante (tryTop?)
            try {
                msg_ptr->apply(_board);  // might be null
            } catch (const std::exception &e) {
                std::cerr << "Exception caught in client: '"
                          << e.what() << "'" << std::endl;
            } catch (...) {
                std::cerr << "Unknown error caught in client.\n";
            }
            recvQueue.pop();
        }

        // mainGameScreen.run()
            // refresh (MainGameScreen)
            // draw (MainGameScreen)
            // read from SDL (MainGameScreen)
            // TRY: board_.move() (MainGameScreen)
        // send (con una queue) // no bloqueante (push)
        // sleep para fps
    //}
    recvThread.join();
    sendThread.join();
}
/*Client::Client movePieze(Position&& from, Position&& to){

}*/

BlockingQueue<std::shared_ptr<Message>>* Client::getQueue(){
    return &sendQueue;
}

Client::Client(const char *host, const char *service, Board &board) : proxy(), _board(board) {
    proxy.connect(host, service);
    id = -1;
    // std::cout << "Choose your name: ";
    // std::getline(std::cin, name);
    // int room_id;
    // std::cout << "Choose a room: ";
    // std::cin >> room_id;
}

