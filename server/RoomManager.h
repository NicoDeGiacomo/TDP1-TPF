//
// Created by ale on 9/11/2021.
//

#ifndef QUANTUM_CHESS_ROOMMANAGER_H
#define QUANTUM_CHESS_ROOMMANAGER_H
#include "Socket.h"
#include "Room.h"
#include <map>
#include <thread>

class RoomManager {
private:
    Socket acceptor;
    std::map<int,Room> rooms;
public:
    RoomManager();
    void start();
};


#endif //QUANTUM_CHESS_ROOMMANAGER_H
