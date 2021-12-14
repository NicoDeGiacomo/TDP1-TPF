#include <iostream>
#include <thread>
#include <Protocol.h>
#include <RoomManager.h>
#include <Message.h>
#include "StageMode.h"

RoomManager::RoomManager(Socket &acceptor) : acceptor(acceptor) {}

void RoomManager::run() {
    while (!acceptor.isNotActive()){
        Socket peer;
        try {
            peer = acceptor.accept();
        } catch (ClosedSocketException &e) {
            std::cout << "ClosedSocketException\n";
            this->stop();
            return;
        }

        ClientProxy client(peer);
        StageMode::log("New Client!");
        StageMode::log("Receiving room id");
        std::shared_ptr<Message> room_id_msg = client.recv();
        if (room_id_msg->getType() != ROOM_ID_CHAR)
            throw std::runtime_error("First message should be the room id");

        std::string room_id = room_id_msg->getMessage();
        StageMode::log(std::string("Client wants to enter room: ") + room_id);

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
    }
    this->stop();
}

void RoomManager::stop() {
    for (auto& room : rooms)
        room.second.close();
    this->acceptor.shutdown();
}