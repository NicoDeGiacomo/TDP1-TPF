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
    //std::list<Socket> listOfPeers;
    BlockingQueue<Message> queueToSend;
    std::thread senderThread;
    /*std::list<std::thread> receiverThreads;*/
    BlockingQueue<Message> queueOfReceived;
    Player playerWhite;
    Player playerBlack;
    std::list<Player> _spectators;
    int roomNumber;
public:
    Room();
    //TODO: fix error when putting this in constructor
    void setRoomNumber(int number);

    bool isRoom(int number);

    void addClient(Socket &&socket);

    void runSenderThread(std::list<Player> *spectators,
                         Player* white,
                         Player* black,
                         BlockingQueue<Message> *queue);

    void runReceiverThread(Player *player, BlockingQueue<std::string> *queue);

    void joinAllThreads();
};


#endif //QUANTUM_CHESS_ROOM_H
