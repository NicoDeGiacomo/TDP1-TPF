#ifndef QUANTUM_CHESS_ROOM_H
#define QUANTUM_CHESS_ROOM_H

#include <Socket.h>
#include <list>
#include <thread>
#include "BlockingQueue.h"
#include "Player.h"
#include "SendThread.h"

class Room {
private:
    BlockingQueue<std::shared_ptr<Message>> queueOfReceived;
    std::list<Player> players;
    Board board;
    Chat chat;
    SendThread sendThread;
    bool white;
    bool black;
    int next_id;
    void sendNamesToClient(ClientProxy &client);
    void assignPlayerType(ClientProxy &client);
public:
    Room() = delete;
    
    Room(ClientProxy &client);

    void addClient(ClientProxy &client);

    void cleanInactivePlayers();

    void close();

    bool isEmpty() const;

    ~Room();
};


#endif //QUANTUM_CHESS_ROOM_H
