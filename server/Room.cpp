#include <iostream>
#include "Room.h"
#include "Protocol.h"
#include <PlayerNameMessage.h>
#include <PlayerTypeMessage.h>
#include <SeedMessage.h>

void Room::sendNamesToClient(ClientProxy &client) {
    for (auto &p : players) {
        int id = p.getId();
        client.send(std::make_shared<PlayerNameMessage>(chat.getName(id), id));
    }
    
    for (auto &s : _spectators) {
        int id = s.getId();
        client.send(std::make_shared<PlayerNameMessage>(chat.getName(id), id));
    }
}


void Room::addClient(ClientProxy &client) {
    //TODO: this list of peers should be protected, can add client while sending messages
    //this->listOfPeers.push_front(std::move(socket));
    //TODO: this is placeholder, it shouldnt receive a socket, rooms should receive players

    std::cout << "SEED: " << board.getSeed() << "\n";

    client.setId(next_id);
    if (players.empty()) {
        client.send(std::make_shared<PlayerTypeMessage>(WHITE_CHAR));
        client.send(std::make_shared<SeedMessage>(board.getSeed()));
        sendNamesToClient(client);
        players.emplace_back(client, queueOfReceived);
        std::cout << "white player created" << std::endl;
        players.back().startReceivingMessages();
        for (const auto& move: board.getCurrentMoves()) {
            players.back().send(move->getMoveMessage());
        }
    } else if (players.size() == 1) {
        client.send(std::make_shared<PlayerTypeMessage>(BLACK_CHAR));
        client.send(std::make_shared<SeedMessage>(board.getSeed()));
        sendNamesToClient(client);
        players.emplace_back(client, queueOfReceived);
        std::cout << "black player created" << std::endl;
        players.back().startReceivingMessages();
        for (const auto& move: board.getCurrentMoves()) {
            players.back().send(move->getMoveMessage());
        }
    } else {
        client.send(std::make_shared<PlayerTypeMessage>(SPECTATOR_CHAR));
        client.send(std::make_shared<SeedMessage>(board.getSeed()));
        sendNamesToClient(client);
        this->_spectators.emplace_front(client, queueOfReceived);
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
    // . "players[BLACK_PLAYER].startReceivingMessages();" .
    // implies that we are throwing a new thread
    // and we need to manually join it? idk,
    // each player could join its threads in their destructor
    for(auto & player : _spectators)
        player.join();
    for(auto & player : players)
        player.join();
    // playerWhite.join();
    // playerBlack.join();
    //now here the join of sender thread its ok because we launch it
    // if (senderThread.joinable())
    //     senderThread.join();
    sendThread.join();

    std::cout << "all threads joined" << std::endl;
}

Room::Room(ClientProxy &client) : sendThread(queueOfReceived, players, _spectators, board, chat), 
                                            next_id(0) {
    sendThread.start();
    this->addClient(client);
}

Room::~Room() {
    //TODO: need to force join threads from destructor
    //this->joinAllThreads();
}
