//
// Created by ale on 9/11/2021.
//

#include <iostream>
#include <thread>
#include <ProtectedString.h>
#include <list>
#include "RoomManager.h"

RoomManager::RoomManager(){
    this->acceptor.bind("7777");
    this->acceptor.listen(6);
    //TODO: placeholder, only using one room and one list of clients
    this->listOfRooms.emplace_front();
}

void RoomManager::start() {
    //TODO: need to look for dead threads and shutdown everything after finish chat.
    //placeholder to only accept i clients, then go join the threads
    int i = 0;
    while (true && i != 3){
        Socket peer = acceptor.accept();
        if (peer.isNotActive())
            //proceed to clean and shutdown threads
            break;
        std::cout << "valid socket accepted" << std::endl;

        //TODO: process where the new client wants to go, which room spectator or player
        //placeholder, added new client to first room
        this->listOfRooms.front().addClient(std::move(peer));
        i++;
    }
    for (auto& room : listOfRooms) {
        room.joinAllThreads();
    }
}
