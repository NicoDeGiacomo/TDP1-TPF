//
// Created by ale on 9/11/2021.
//

#ifndef QUANTUM_CHESS_CLIENT_H
#define QUANTUM_CHESS_CLIENT_H


#include <Board.h>
#include "Socket.h"
#include "ServerProxy.h"
#include "GameScene.h"
#include "SceneManager.h"

#define LOGIN_SCENE "Login"
#define LOBBY_SCENE "Lobby"
#define GAME_SCENE "Game"

class Client {
private:
    SceneManager sceneManager;
    ServerProxy proxy;
    Board _board;
    BlockingQueue<std::shared_ptr<std::string>> chatQueue;
    //GameScene mainGameScreen;
    int id;
    char playerType;
    bool gameFinished;
    std::string name;
    BlockingQueue<std::shared_ptr<Message>> recvQueue;
    BlockingQueue<std::shared_ptr<Message>> sendQueue;
public:
    Client(const char *host, const char *service);

    void run();

    BlockingQueue<std::shared_ptr<Message>> *getQueue();
};


#endif //QUANTUM_CHESS_CLIENT_H
