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
    BlockingQueue<Message> queueToSend;
    std::thread senderThread;
    BlockingQueue<std::unique_ptr<Message>> queueOfReceived;
    std::list<Player> _spectators;
    Player playerBlack;
    Player playerWhite;
    int roomNumber;
public:
    Room() = delete;
    Room(int number, Socket&& socket);

    bool isRoom(int number) const;

    void addClient(Socket &&socket);

    void runSenderThread(std::list<Player> *spectators,
                         Player* white,
                         Player* black,
                         BlockingQueue<Message> *queue);

    void joinAllThreads();

    ~Room();
};


#endif //QUANTUM_CHESS_ROOM_H
