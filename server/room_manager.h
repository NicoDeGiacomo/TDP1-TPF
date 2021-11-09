//
// Created by civini on 9/11/2021.
//

#ifndef QUANTUM_CHESS_ROOM_MANAGER_H
#define QUANTUM_CHESS_ROOM_MANAGER_H
#include <vector>
#include <set>
#include <mutex>
#include "Socket.h"
#include "client.h"
#include "room.h"

class RoomManager
{
private:
    static RoomManager* roomManager;
    RoomManager();
    std::vector<Room> rooms;
    std::set<int> used_numbers;
    std::mutex m;
public:
    static RoomManager* getRoomManager();
    int createRoom();
    void joinRoomWhites(int room, Client whites);
    void joinRoomBlacks(int room, Client blacks);
    bool joinRoomSpectator(int room, Client spectator);
    void endRoom(int room);
};

RoomManager* RoomManager::roomManager = nullptr;

RoomManager::RoomManager(){
}

RoomManager* RoomManager::getRoomManager(){
    if (roomManager == nullptr){
        roomManager = new RoomManager();
    }
    return roomManager;
}

int RoomManager::createRoom(){
    std::lock_guard<std::mutex> lock(m);
    int room_number = 1;
    while (used_numbers.find(room_number)!=used_numbers.end()){
        room_number++;
    }
    rooms.push_back(Room(room_number));
    used_numbers.insert(room_number);
    return room_number;
}

void RoomManager::joinRoomWhites(int room_num, Client whites){
    std::lock_guard<std::mutex> lock(m);
    if (used_numbers.find(room_num)==used_numbers.end()){
        Room room(room_num);
        room.addWhites(whites);
        rooms.push_back(room);
        used_numbers.insert(room_num);
        return;
    }
    for (Room& room : rooms){
        if (room.getRoomNumber()==room_num){
            room.addWhites(whites);
            return;
        }
    }   
}

void RoomManager::joinRoomBlacks(int room_num, Client blacks){
    std::lock_guard<std::mutex> lock(m);
    if (used_numbers.find(room_num)==used_numbers.end()){
        Room room(room_num);
        room.addBlacks(blacks);
        rooms.push_back(room);
        used_numbers.insert(room_num);
        return;
    }
    for (Room& room : rooms){
        if (room.getRoomNumber()==room_num){
            room.addBlacks(blacks);
            return;
        }
    }
}

bool RoomManager::joinRoomSpectator(int room_num, Client spectator){
    std::lock_guard<std::mutex> lock(m);
    if (used_numbers.find(room_num)==used_numbers.end()){
        Room room(room_num);
        room.addSpectator(spectator);
        rooms.push_back(room);
        used_numbers.insert(room_num);
        return true;
    }
    for (Room& room : rooms){
        if (room.getRoomNumber()==room_num){
            return room.addSpectator(spectator);
        }
    }
}

RoomManager::~RoomManager(){
}


#endif //QUANTUM_CHESS_ROOM_MANAGER_H
