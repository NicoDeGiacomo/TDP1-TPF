//
// Created by ale on 12/11/21.
//

#include <iostream>
#include "Room.h"
#include "Protocol.h"

bool Room::isRoom(int number) const{
    return number == roomNumber;
}

void Room::addClient(Socket &socket) {
    //TODO: this list of peers should be protected, can add client while sending messages
    //this->listOfPeers.push_front(std::move(socket));
    //TODO: this is placeholder, it shouldnt receive a socket, rooms should receive players
    if (this->playerWhite.isVacant()) {
        //TODO: think if passing Queue To Send is needed, right now is just for debugging
        this->playerWhite.initPlayer(socket, next_id, WHITE_CHAR, board.getSeed());
        std::cout << "white player created" << std::endl;
        this->playerWhite.startReceivingMessages();
        for (const auto& move: board.getCurrentMoves()) {
            this->playerWhite.send(move->getMoveMessage());
        }
    }
    else if (this->playerBlack.isVacant()) {
        //TODO: think if passing Queue To Send is needed, right now is just for debugging
        this->playerBlack.initPlayer(socket, next_id, BLACK_CHAR, board.getSeed());
        std::cout << "black player created" << std::endl;
        this->playerBlack.startReceivingMessages();
        for (const auto& move: board.getCurrentMoves()) {
            this->playerBlack.send(move->getMoveMessage());
        }
    }
    else {
        //TODO: think if passing Queue To Send is needed, right now is just for debugging
        this->_spectators.emplace_front(socket, queueOfReceived, next_id, SPECTATOR_CHAR, board.getSeed());
        std::cout << "spectator created" << std::endl;
        this->_spectators.front().startReceivingMessages();
        for (const auto& move: board.getCurrentMoves()) {
            this->_spectators.front().send(move->getMoveMessage());
        }
    }
    next_id++;
}

void Room::joinAllThreads() {
    //TODO: read and fix this join issue
    // its debatable if manually joining violates RAII, does
    // . "this->playerBlack.startReceivingMessages();" .
    // implies that we are throwing a new thread
    // and we need to manually join it? idk,
    // each player could join its threads in their destructor
    for(auto & player : _spectators)
        player.join();
    playerWhite.join();
    playerBlack.join();
    //now here the join of sender thread its ok because we launch it
    // if (senderThread.joinable())
    //     senderThread.join();
    sendThread.join();

    std::cout << "all threads joined" << std::endl;
}

Room::Room(int number, Socket &socket) 
                : roomNumber(number),
                  playerBlack(queueOfReceived),
                  playerWhite(queueOfReceived),
                  sendThread(queueOfReceived, playerWhite, playerBlack, _spectators, board),
                  next_id(0) {
    sendThread.start();
    this->addClient(socket);
}

Room::~Room() {
    //TODO: need to force join threads from destructor
    //this->joinAllThreads();
}
