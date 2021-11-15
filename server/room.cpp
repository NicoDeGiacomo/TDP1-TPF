#include "room.h"
#include <vector>
#include "Socket.h"
#include "client.h"


// Room::Room(int room_number): room_number(room_number){
// }

// int Room::getRoomNumber(){
//     return room_number;
// }

// bool Room::addWhites(Client whites){
//     this->whites = whites;
//     return true;
// }

bool Room::addBlacks(Client blacks){
    this->blacks = blacks;
    return true;
}

bool Room::addSpectator(Client spectator){
    if (spectators.size()>= 3) return false;
    spectators.push_back(spectator);
    return true;
}

Room::~Room(){
}
