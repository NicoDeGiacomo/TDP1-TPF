#include <iostream>
#include <thread>
#include <list>
#include <Protocol.h>
#include <RoomManager.h>
#include <Message.h>
#include "StageMode.h"

RoomManager::RoomManager(Socket &acceptor) : acceptor(acceptor) {}

void RoomManager::run() {
    //std::list<std::reference_wrapper<Room>> listOfRooms;
    //TODO: need to look for dead threads and shutdown everything after finish chat.
    while (!acceptor.isNotActive()){
        Socket peer;
        try {
            peer = acceptor.accept();
        } catch (ClosedSocketException &e) {
            std::cout << "ClosedSocketException\n";
            this->stop();
            return;
        }

        if (peer.isNotActive())
            //proceed to clean and shutdown threads
            break;
        // std::cout << "valid socket accepted" << std::endl;
        //TODO: protocol for reciving from the client the room number and position wanted
        // int roomNumber = 1;

        ClientProxy client(peer);
        StageMode::log("New Client!");
        StageMode::log("Receiving room id");
        std::shared_ptr<Message> room_id_msg = client.recv();
        // std::shared_ptr<Message> player_type_msg = client.recv();
        if (room_id_msg->getType() != ROOM_ID_CHAR)
            throw std::runtime_error("First message should be the room id");
        // if (player_type_msg->getType() != PLAYER_TYPE_CHAR)
        //     throw std::runtime_error("Second message should be the player type (Player/Spectator)");

        std::string room_id = room_id_msg->getMessage();
        StageMode::log(std::string("Client wants to enter room: ") + room_id);
        // std::string player_type = player_type_msg->getMessage();

        try {
            rooms.at(room_id).addClient(client);
        } catch (const std::out_of_range &e) {
           rooms.emplace(room_id, client); 
        }

        StageMode::log("Client added with no errors");
        
        for (auto it = rooms.begin(); it != rooms.end(); ) {
            it->second.cleanInactivePlayers();
            if (it->second.isEmpty()) {
                it->second.close();
                it = rooms.erase(it);
            } else {
                ++it;
            }
        }

        StageMode::log("Number of rooms: " + std::to_string(rooms.size()));
        //TODO: process where the new client wants to go, which room spectator or player
    }
    //TODO: this is bad, roomManager is never throwing new thread, how does he know that
    //he needs to join the rooms, join should be in the destructor of rooms in this case
    for (auto& room : rooms)
        room.second.close();

    //listOfRooms.clear();
}

void RoomManager::stop() {
    for (auto& room : rooms)
        room.second.close();
    this->acceptor.shutdown();
}