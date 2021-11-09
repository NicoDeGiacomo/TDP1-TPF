//
// Created by civini on 9/11/2021.
//

#ifndef QUANTUM_CHESS_ROOM_H
#define QUANTUM_CHESS_ROOM_H
#include <vector>
#include "Socket.h"
#include "client.h"

class Room
{
private:
    Client whites;
    Client blacks;
    std::vector<Client> spectators;
    int room_number;
public:
    Room(int room_number);
    int getRoomNumber();
    bool addWhites(Client whites);
    bool addBlacks(Client blacks);
    bool addSpectator(Client spectator);
    ~Room();
};

#endif //QUANTUM_CHESS_ROOM_H
