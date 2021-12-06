//
// Created by ale on 9/11/2021.
//

#include <string>
#include <iostream>
#include <Socket.h>
#include <thread>
#include <Message.h>
#include <Protocol.h>
#include "Client.h"
#include "RecvThread.h"
#include "SendThread.h"
#include "SceneManager.h"
#include "LoginScene.h"
#include "LobbyScene.h"

void Client::run() {
    RecvThread recvThread(proxy, recvQueue);
    SendThread sendThread(proxy, _board, id, sendQueue, chatQueue);
    recvThread.start();
    sendThread.start();
    // mainGameScreen()

    //std::string user_name = mainGameScreen.login();

    //LoginScene login;
    //add scene main game screen
    sceneManager.loadScene(LOGIN_SCENE);
    sceneManager.updateLoopActiveScene(); //maybe this loops should be iterated here? instead of them knowing when to break
    sceneManager.loadScene(LOBBY_SCENE);
//    while (!gameFinished){
        sceneManager.updateLoopActiveScene(); //maybe this loops should be iterated here? instead of them knowing when to break, kinda like Game_Scene loop
//        SDL_Delay(1000/60); //todo: should ask for monitor refresh rate, this is capped at 60fps
    //}
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
                msg_ptr->apply(_board, chatQueue);
            } catch (const std::exception &e) {
                std::cerr << "Exception caught in client: '"
                          << e.what() << "'" << std::endl;
            } catch (...) {
                std::cerr << "Unknown error caught in client.\n";
            }
        }

        //SDL_Delay(1000/60); //todo: should ask for monitor refresh rate, this is capped at 60fps
        if (_board.isFinished()){
            sceneManager.updateLoopActiveScene();
            //mainGameScreen.endMessage(SPECTATOR_CHAR); cant do this anymore, need to think another way
            std::cout << "game finished" << std::endl;
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
            : proxy(host, service), _board(false, proxy.getSeed()), chatQueue() {
    gameFinished = false;

    //std::cin.ignore();
    //proxy.connect(host, service);
    playerType = proxy.getPlayerType();
    id = -1;
    int numberOfRooms = 50; //todo: placeholder, change this to actual number of rooms
    sceneManager.addScene(std::make_unique<LoginScene>(), LOGIN_SCENE);
    sceneManager.addScene(std::make_unique<LobbyScene>(numberOfRooms), LOBBY_SCENE);
    //sceneManager.loadScene("LoginScene");
    sceneManager.addScene(std::make_unique<GameScene>(_board,
                                                      &sendQueue,
                                                      chatQueue,
                                                      proxy.getPlayerType(),
                                                      gameFinished),GAME_SCENE);
    // std::cout << "Choose your name: ";
    // std::getline(std::cin, name);
    // int room_id;
    // std::cout << "Choose a room: ";
    // std::cin >> room_id;
}

