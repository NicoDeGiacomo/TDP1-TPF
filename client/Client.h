#ifndef QUANTUM_CHESS_CLIENT_H
#define QUANTUM_CHESS_CLIENT_H


#include <Board.h>
#include "Socket.h"
#include "ServerProxy.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "Chat.h"
#include "SendThread.h"
#include "RecvThread.h"

#define LOGIN_SCENE "Login"
#define LOBBY_SCENE "Lobby"
#define GAME_SCENE "Game"
#define CONFIG_SCENE "Config"

class Client {
private:
    SceneManager sceneManager;
    ServerProxy proxy;
    Board _board;
    Chat chat;
    bool gameFinished;
    bool mute;
    std::string name;
    char playerType;
    std::string roomId;
    BlockingQueue<std::shared_ptr<Message>> recvQueue;
    BlockingQueue<std::shared_ptr<Message>> sendQueue;
    void initMessages();
public:
    Client(const char *host, const char *service, bool mute=false);

    void run();

    BlockingQueue<std::shared_ptr<Message>> *getQueue();
};


#endif //QUANTUM_CHESS_CLIENT_H
