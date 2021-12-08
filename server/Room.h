//
// Created by ale on 12/11/21.
//

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
    int roomNumber;
    BlockingQueue<std::shared_ptr<Message>> queueOfReceived;
    std::list<Player> _spectators;
    Player playerBlack;
    Player playerWhite;
    Board board;
    Chat chat;
    SendThread sendThread;
    int next_id;
public:
    Room() = delete;
    
    Room(int number, Socket &socket);

    bool isRoom(int number) const;

    void addClient(Socket &socket);

    void joinAllThreads();

    ~Room();
};


#endif //QUANTUM_CHESS_ROOM_H
