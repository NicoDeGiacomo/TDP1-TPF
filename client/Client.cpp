//
// Created by ale on 9/11/2021.
//

#include <string>
#include <iostream>
#include <Socket.h>
#include <thread>
#include <Message.h>
#include <PlayerNameMessage.h>
#include <Protocol.h>
#include "Client.h"
#include "RecvThread.h"
#include "SendThread.h"
#include "SceneManager.h"
#include "LoginScene.h"
#include "LobbyScene.h"
#include "ConfigScene.h"

void Client::run() {
    RecvThread recvThread(proxy, recvQueue);
    SendThread sendThread(proxy, _board, chat, id, sendQueue);
    recvThread.start();
    sendThread.start();
    // mainGameScreen()

    //std::string user_name = mainGameScreen.login();

    //LoginScene login;
    //add scene main game screen
    sceneManager.loadScene(LOGIN_SCENE);
    sceneManager.updateLoopActiveScene(); //maybe this loops should be iterated here? instead of them knowing when to break
    
    sendQueue.produce(std::make_shared<PlayerNameMessage>(name));
    sceneManager.loadScene(LOBBY_SCENE);

    sceneManager.updateLoopActiveScene();
    // send room_id

    sceneManager.loadScene(GAME_SCENE);
    
    while (!gameFinished) {
        sceneManager.updateLoopActiveScene();
        bool moreMessagesToProcess = true;
        
        while(moreMessagesToProcess) {
            std::shared_ptr<Message> msg_ptr = recvQueue.popIfNotEmpty();

            if (!msg_ptr) {
                moreMessagesToProcess = false;
                continue;
            }
            try {
                msg_ptr->apply(_board, chat);
            } catch (const std::exception &e) {
                std::cerr << "Exception caught in client: '"
                          << e.what() << "'" << std::endl;
            } catch (...) {
                std::cerr << "Unknown error caught in client.\n";
            }
        }
        if (_board.isFinished()){
            //sceneManager.updateLoopActiveScene();
            //mainGameScreen.endMessage(SPECTATOR_CHAR); cant do this anymore, need to think another way
            std::cout << "game finished with checkmate" << std::endl;
            break; 
        }
    }
    recvThread.stop();
    recvThread.join();
    sendThread.stop();
    sendThread.join();
}

BlockingQueue<std::shared_ptr<Message>>* Client::getQueue(){
    return &sendQueue;
}

Client::Client(const char *host, const char *service)
            : proxy(host, service), _board(false, proxy.getSeed()) {
    gameFinished = false;

    //std::cin.ignore();
    //proxy.connect(host, service);
    playerType = proxy.getPlayerType();
    id = -1;
    int numberOfRooms = 50; //todo: placeholder, change this to actual number of rooms
    std::unique_ptr<Scene> configScene = std::make_unique<ConfigScene>();
    sceneManager.addScene(std::make_unique<LoginScene>(configScene.get(), name), LOGIN_SCENE);
    sceneManager.addScene(std::make_unique<LobbyScene>(numberOfRooms, configScene.get()), LOBBY_SCENE);
    sceneManager.addScene(std::move(configScene), CONFIG_SCENE);
    //sceneManager.loadScene("LoginScene");
    sceneManager.addScene(std::make_unique<GameScene>(_board,
                                                      &sendQueue,
                                                      chat.getQueue(),
                                                      proxy.getPlayerType(),
                                                      gameFinished),GAME_SCENE);
    
    // proxy.send(std::make_shared<PlayerInfoMessage>());
}

