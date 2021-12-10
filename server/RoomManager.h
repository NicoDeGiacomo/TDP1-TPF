#ifndef QUANTUM_CHESS_ROOMMANAGER_H
#define QUANTUM_CHESS_ROOMMANAGER_H
#include "Socket.h"
#include "Room.h"
#include <map>
#include <string>

class RoomManager {
private:
    Socket acceptor;
    std::map<std::string,Room> rooms;
public:
    RoomManager();
    void start();
};


#endif //QUANTUM_CHESS_ROOMMANAGER_H
