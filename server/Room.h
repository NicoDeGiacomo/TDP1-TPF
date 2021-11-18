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

class Room {
private:
    std::thread senderThread;
    BlockingQueue<std::shared_ptr<Message>> queueOfReceived;
    std::list<Player> _spectators;
    Player playerBlack;
    Player playerWhite;
    int roomNumber;
    Board board;
public:
    Room() = delete;
    Room(int number, Socket&& socket);

    bool isRoom(int number) const;

    void addClient(Socket &&socket);

    void runSenderThread(std::list<Player> *spectators,
                         Player* white,
                         Player* black,
                         BlockingQueue<std::shared_ptr<Message>>* queue);

    void joinAllThreads();

    ~Room();
};


#endif //QUANTUM_CHESS_ROOM_H
