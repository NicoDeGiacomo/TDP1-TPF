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
    SendThread sendThread(proxy, id);
    recvThread.start();
    sendThread.start();

    while (1) {
        std::shared_ptr<Message> msg_ptr = recvQueue.top();
        msg_ptr->apply(board);
        // sendQueue.produce(std::move(msg_ptr));
        recvQueue.pop();
    }
    
    recvThread.join();
    sendThread.join();
}


Client::Client(const char *host, const char *service) : proxy() {
    proxy.connect(host, service);
    // std::cout << "Choose your name: ";
    // std::getline(std::cin, name);
    // int room_id;
    // std::cout << "Choose a room: ";
    // std::cin >> room_id;
}

