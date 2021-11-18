//
// Created by ale on 9/11/2021.
//

#ifndef QUANTUM_CHESS_CLIENT_H
#define QUANTUM_CHESS_CLIENT_H


#include <Board.h>

class Client {
private:
    Board board;
    std::string id;
public:
    Client();

    void start();

    void runSenderThread(Socket* client);

    void runReceiverThread(Socket* client);
};


#endif //QUANTUM_CHESS_CLIENT_H
