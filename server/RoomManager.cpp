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
}

void RoomManager::start() {
    std::list<std::reference_wrapper<Room>> listOfRooms;
    //TODO: need to look for dead threads and shutdown everything after finish chat.
    //placeholder to only accept i clients, then go join the threads
    int i = 0;
    while (true && i != 3){
        Socket peer = acceptor.accept();
        if (peer.isNotActive())
            //proceed to clean and shutdown threads
            break;
        std::cout << "valid socket accepted" << std::endl;
        //TODO: protocol for reciving from the client the room number and position wanted
        int roomNumber = 1;
        bool roomExists = false;
        for (Room& room : listOfRooms){
            if (!room.isRoom(roomNumber)) continue;
            room.addClient(std::move(peer));
            roomExists = true;
            break;
        }
        if (!roomExists){
            Room room;
            room.setRoomNumber(roomNumber);
            room.addClient(std::move(peer));
            listOfRooms.push_back(room);
        }
        
        //TODO: process where the new client wants to go, which room spectator or player
        //placeholder, added new client to first room
        i++;//keep this until other method of closing it is implemented
    }
    for (auto& room : listOfRooms) {
        room.get().joinAllThreads();
    }
}
