//
// Created by ale on 9/11/2021.
//

#include <iostream>
#include <thread>
#include <list>
#include "RoomManager.h"

RoomManager::RoomManager(){
    //todo: dont hardcode this
    this->acceptor.bind("7777");
    this->acceptor.listen(6);
}

void RoomManager::start() {
    //std::list<std::reference_wrapper<Room>> listOfRooms;
    //TODO: need to look for dead threads and shutdown everything after finish chat.
    while (true){
        Socket peer = acceptor.accept();
        if (peer.isNotActive())
            //proceed to clean and shutdown threads
            break;
        // std::cout << "valid socket accepted" << std::endl;
        //TODO: protocol for reciving from the client the room number and position wanted
        int roomNumber = 1;
        bool roomExists = false;
        for (Room& room : listOfRooms){
            if (!room.isRoom(roomNumber)) continue;
            room.addClient(peer);
            roomExists = true;
            break;
        }
        if (!roomExists){
            listOfRooms.emplace_back(roomNumber, peer);
        }
        
        //TODO: process where the new client wants to go, which room spectator or player
    }
    //TODO: this is bad, roomManager is never throwing new thread, how does he know that
    //he needs to join the rooms, join should be in the destructor of rooms in this case
    for (auto& room : listOfRooms) {
        room.joinAllThreads();
    }
    //listOfRooms.clear();
}
