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
    std::list<Player> _spectators;
    Board board;
    Chat chat;
    SendThread sendThread;
    int next_id;
    void sendNamesToClient(ClientProxy &client);
public:
    Room() = delete;
    
    Room(ClientProxy &client);

    void addClient(ClientProxy &client);

    void joinAllThreads();

    ~Room();
};


#endif //QUANTUM_CHESS_ROOM_H
