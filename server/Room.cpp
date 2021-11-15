//
// Created by ale on 12/11/21.
//

#include <iostream>
#include "Room.h"
#include "Protocol.h"

Room::Room(){
    //TODO: use sender thread class
    //start the send thread
    //habria que diferenciar entre jugador blanco negro y espectador en el send?
    this->senderThread =
            std::thread(&Room::runSenderThread,
                        this,
                        &this->_spectators,
                        &this->playerWhite,
                        &this->playerBlack,
                        &this->queueToSend);
}

void Room::setRoomNumber(int number){
    roomNumber = number;
}

bool Room::isRoom(int number){
    return number == roomNumber;
}

void Room::runSenderThread(std::list<Player>* spectators,
                           Player* white,
                           Player* black,
                           BlockingQueue<Message>* queue){
    std::cout << "running sender sv thread" << std::endl;
    while (true) {
        const Message message = queue->top();
        queue->pop();
        try {
            for (auto &spectator: *spectators) {
                spectator.send(message);
            }
            white->send(message);
            black->send(message);
        } catch (ClosedSocketException& e){
            //TODO: for some reason this catch isnt catching, the socket
            //is throwing the error receiving bytes exception instead
            std::cout << e.what() << std::endl;
            return;
        }
        std::cout << "-server just sent: " << message.getMessage() << std::endl;
    }
}

void Room::addClient(Socket &&socket) {
    //TODO: this list of peers should be protected, can add client while sending messages
    //this->listOfPeers.push_front(std::move(socket));
    //TODO: this is placeholder, it shouldnt receive a socket, rooms should receive players
    if (this->playerWhite.isVacant()) {
        //TODO: think if passing Queue To Send is needed, right now is just for debugging
        this->playerWhite.initPlayer(std::move(socket), &this->queueOfReceived, &this->queueToSend);
        std::cout << "white player created" << std::endl;
        this->playerWhite.startReceivingMessages();
    }
    else if (this->playerBlack.isVacant()) {
        //TODO: think if passing Queue To Send is needed, right now is just for debugging
        this->playerBlack.initPlayer(std::move(socket), &this->queueOfReceived, &this->queueToSend);
        std::cout << "black player created" << std::endl;
        this->playerBlack.startReceivingMessages();
    }
    else {
        //TODO: think if passing Queue To Send is needed, right now is just for debugging
        this->_spectators.emplace_front(std::move(socket), &this->queueOfReceived, &this->queueToSend);
        std::cout << "spectator created" << std::endl;
        this->_spectators.front().startReceivingMessages();
    }
    //TODO: use receiver thread class instead
    /*this->receiverThreads.push_front(
            std::thread(&Room::runReceiverThread,
                        this,
                        &this->_spectators.front(),
                        &this->queueOfReceived));*/
}

/*void Room::runReceiverThread(Player *player, BlockingQueue<std::string>* queue){
    std::cout << "running receiver sv thread" << std::endl;
    while (true) {
        //TODO: remove this 4 hardcoded, need to add protocol
        char received[4];
        try {
            player->receive(received, 4);
        } catch (ClosedSocketException& e){
            std::cout << e.what() << std::endl;
            return;
        }
        std::cout << "--server received" << std::endl;
        //Message* msg = Protocol::getMessageFromBytes(received);
        for (auto &c : received){
            std::cout << c;
        }
        std::string buffer(received, received + 4);
        queue->produce(std::move(buffer));
        std::cout << std::endl << "---" << std::endl;
    }
}*/

void Room::joinAllThreads() {
    for(auto & player : _spectators)
        player.join();
    playerWhite.join();
    playerBlack.join();
    std::cout << "all threads joined" << std::endl;
}