//
// Created by ale on 9/11/2021.
//

#ifndef QUANTUM_CHESS_ROOMMANAGER_H
#define QUANTUM_CHESS_ROOMMANAGER_H
#include "ProtectedString.h"
#include "Socket.h"
#include "Room.h"
#include <list>
#include <thread>

class RoomManager {
private:
    Socket acceptor;
    ProtectedString protectedString;
    //std::list<Socket> listOfPeers;
    //std::list<Room> listOfRooms;
    //Room room;
    //std::list<std::thread> receiverThreads;
    std::list<std::thread> senderThreads;
public:
    RoomManager();
    void start();
};


#endif //QUANTUM_CHESS_ROOMMANAGER_H
