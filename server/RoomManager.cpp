#include <iostream>
#include <thread>
#include <list>
#include <Protocol.h>
#include <RoomManager.h>
#include <Message.h>

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
        // int roomNumber = 1;

        ClientProxy client(peer);
        std::cout << "New Client!" << std::endl;

        std::cout << "Receiving room id" << std::endl;
        std::shared_ptr<Message> room_id_msg = client.recv();
        // std::shared_ptr<Message> player_type_msg = client.recv();
        if (room_id_msg->getType() != ROOM_ID_CHAR)
            throw std::runtime_error("First message should be the room id");
        // if (player_type_msg->getType() != PLAYER_TYPE_CHAR)
        //     throw std::runtime_error("Second message should be the player type (Player/Spectator)");

        std::string room_id = room_id_msg->getMessage();
        std::cout << "Client wants to enter room: " << room_id << std::endl;
        // std::string player_type = player_type_msg->getMessage();

        try {
            rooms.at(room_id).addClient(client);
        } catch (...) {
           rooms.emplace(room_id, client); 
        }
        
        //TODO: process where the new client wants to go, which room spectator or player
    }
    //TODO: this is bad, roomManager is never throwing new thread, how does he know that
    //he needs to join the rooms, join should be in the destructor of rooms in this case
    // for (auto& room : listOfRooms) {
    //     room.joinAllThreads();
    // }
    //listOfRooms.clear();
}
