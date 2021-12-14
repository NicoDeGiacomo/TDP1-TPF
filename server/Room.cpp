#include <iostream>
#include "Room.h"
#include "Protocol.h"
#include <PlayerNameMessage.h>
#include <PlayerTypeMessage.h>
#include <SeedMessage.h>
#include <StageMode.h>

void Room::sendNamesToClient(ClientProxy &client) {
    for (auto &p : players) {
        int id = p.getId();
        client.send(std::make_shared<PlayerNameMessage>(chat.getName(id), id));
    }
}

void Room::assignPlayerType(ClientProxy &client) {
    char real_type = SPECTATOR_CHAR;
    char type = client.recv()->getMessage().at(0);
    if (type == WHITE_CHAR) {
        if (!white) {
            real_type = WHITE_CHAR;
            white = true;
        } else if (!black) {
            real_type = BLACK_CHAR;
            black = true;
        } 
    } else if (type == BLACK_CHAR) {
        if (!black) {
            real_type = BLACK_CHAR;
            black = true;
        } else if (!white) {
            real_type = WHITE_CHAR;
            white = true;
        } 
    }

    client.send(std::make_shared<PlayerTypeMessage>(real_type));
}

void Room::addClient(ClientProxy &client) {
    //TODO: this list of peers should be protected, can add client while sending messages
    //this->listOfPeers.push_front(std::move(socket));
    //TODO: this is placeholder, it shouldnt receive a socket, rooms should receive players

    std::cout << "SEED: " << board.getSeed() << "\n";
    client.setId(next_id);

    assignPlayerType(client);

    client.send(std::make_shared<SeedMessage>(board.getSeed()));
    sendNamesToClient(client);
    this->players.emplace_front(client, queueOfReceived);
    this->players.front().startReceivingMessages();
    for (const auto& move: board.getCurrentMoves()) {
        this->players.front().send(move->getMoveMessage());
    }

    next_id++;
}

void Room::cleanInactivePlayers() {
    for (auto it = players.begin(); it != players.end(); ) {
        if (it->isDead()) {
            StageMode::log("Cleaning client. ID: " + std::to_string(it->getId()));
            it->join();
            it = players.erase(it);
        } else {
            ++it;
        }
    }
}

void Room::interruptAllConnections() {
    //TODO: read and fix this join issue
    // its debatable if manually joining violates RAII, does
    // . "players[BLACK_PLAYER].startReceivingMessages();" .
    // implies that we are throwing a new thread
    // and we need to manually join it? idk,
    // each player could join its threads in their destructor
    for(auto & player : players)
        player.join();

    for (auto it = players.begin(); it != players.end(); ) {
        it->join();
        it = players.erase(it);
        ++it;
    }

    sendThread.join();

    StageMode::log("Closing connections with every client of the room");
}

bool Room::isEmpty() const {
    return this->players.empty();
}

Room::Room(ClientProxy &client) : sendThread(queueOfReceived, players, board, chat), 
                                  white(false), black(false), next_id(0) {
    sendThread.start();
    this->addClient(client);
}

Room::~Room() {
    this->interruptAllConnections();
}
