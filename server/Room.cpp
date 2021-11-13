//
// Created by ale on 12/11/21.
//

#include <iostream>
#include "Room.h"

Room::Room() {
    //TODO: use sender thread class
    //start the send thread
    //habria que diferenciar entre jugador blanco negro y espectador en el send?
    this->senderThread =
            std::thread(&Room::runSenderThread,
                        this,
                        &this->spectators,
                        &this->playerWhite,
                        &this->playerBlack,
                        &this->queueToSend);
}

void Room::runSenderThread(std::list<Player>* spectators,
                           Player* white,
                           Player* black,
                           BlockingQueue<std::string>* queue){
    std::cout << "running sender sv thread" << std::endl;
    while (true) {
        std::string toSend;
        toSend = queue->top();
        queue->pop();
        try {
            for (auto &spectator: *spectators) {
                spectator.send(toSend.c_str(), toSend.length());
            }
            white->send(toSend.c_str(), toSend.length());
            black->send(toSend.c_str(), toSend.length());
        } catch (ClosedSocketException& e){
            //TODO: for some reason this catch isnt catching, the socket
            //is throwing the error receiving bytes exception instead
            std::cout << e.what() << std::endl;
            return;
        }
        std::cout << "-server just sent: " << toSend << std::endl;
    }
}

void Room::addClient(Socket &&socket) {
    //TODO: this list of peers should be protected, can add client while sending messages
    //this->listOfPeers.push_front(std::move(socket));
    //TODO: this is placeholder, it shouldnt receive a socket, rooms should receive players
    if (this->playerWhite.isVacant()) {
        this->playerWhite.initPlayer(std::move(socket), &this->queueOfReceived);
        std::cout << "white player created" << std::endl;
        this->playerWhite.startReceivingMessages();
    }
    else if (this->playerBlack.isVacant()) {
        this->playerBlack.initPlayer(std::move(socket), &this->queueOfReceived);
        std::cout << "black player created" << std::endl;
        this->playerBlack.startReceivingMessages();
    }
    else {
        this->spectators.emplace_front(std::move(socket), &this->queueOfReceived);
        std::cout << "spectator created" << std::endl;
        this->spectators.front().startReceivingMessages();
    }
    //TODO: use receiver thread class instead
    /*this->receiverThreads.push_front(
            std::thread(&Room::runReceiverThread,
                        this,
                        &this->spectators.front(),
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
    for(auto & player : spectators)
        player.join();
    playerWhite.join();
    playerBlack.join();
    std::cout << "all threads joined" << std::endl;
}