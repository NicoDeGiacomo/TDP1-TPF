#include <string>
#include <string.h>
#include <iostream>
#include <Socket.h>
#include <thread>
#include <Message.h>
#include <PlayerNameMessage.h>
#include <RoomIdMessage.h>
#include <PlayerTypeMessage.h>
#include <Protocol.h>
#include "Client.h"
#include "RecvThread.h"
#include "SendThread.h"
#include "SceneManager.h"
#include "LoginScene.h"
#include "LobbyScene.h"
#include "ConfigScene.h"
#include "StageMode.h"

void Client::initMessages() {
    sendQueue.produce(std::make_shared<RoomIdMessage>(roomId));
    
    sendQueue.produce(std::make_shared<PlayerTypeMessage>(playerType));
    std::shared_ptr<Message> type_msg = recvQueue.top();
    if (type_msg->getType() != PLAYER_TYPE_CHAR)
        throw std::runtime_error("First message should be the player type");
    playerType = type_msg->getMessage().at(0);
    recvQueue.pop();

    std::shared_ptr<Message> seed_msg = recvQueue.top();
    if (seed_msg->getType() != SEED_CHAR)
        throw std::runtime_error("Second message should be the seed");
    unsigned int seed;
    memcpy(&seed, seed_msg->getMessage().data(), sizeof(seed));
    StageMode::log(std::string("SEED ") + std::to_string(seed));
    recvQueue.pop();

    _board.setSeed(seed);
}

void Client::run() {
    RecvThread recvThread(proxy, recvQueue);
    SendThread sendThread(proxy, _board, chat, sendQueue);
    sceneManager.loadScene(LOGIN_SCENE);
    sceneManager.updateLoopActiveScene();
    if (gameFinished) return;
    
    sceneManager.loadScene(LOBBY_SCENE);
    sceneManager.updateLoopActiveScene();
    if (gameFinished) return;
    StageMode::log(std::string("client has room id: .") + roomId + ". and type ." + playerType + ".");
    
    proxy.connect();
    recvThread.start();
    sendThread.start();

    this->initMessages();

    sceneManager.addScene(std::make_unique<GameScene>(_board,
                                                      &sendQueue,
                                                      chat.getQueue(),
                                                      playerType,
                                                      gameFinished,
                                                      mute), GAME_SCENE);

    sendQueue.produce(std::make_shared<PlayerNameMessage>(name));
    sceneManager.loadScene(GAME_SCENE);

    while (!gameFinished) {
        sceneManager.updateLoopActiveScene();
        bool moreMessagesToProcess = true;
        
        while(moreMessagesToProcess) {
            std::shared_ptr<Message> msg_ptr;
            try {
                msg_ptr = recvQueue.popIfNotEmpty();
            } catch (const ClosedQueueException &e) {
                gameFinished = true;
                break;
            }

            if (!msg_ptr) {
                moreMessagesToProcess = false;
                continue;
            }
            try {
                msg_ptr->apply(_board, chat);
            } catch (const std::exception &e) {
                StageMode::log(
                    std::string("Exception caught in client: '") + e.what()
                        + "'");
            } 
        }
        if (_board.isFinished()){
            StageMode::log("game finished with checkmate");
        }
    }
    sceneManager.updateLoopActiveScene();
    recvThread.stop();
    recvThread.join();
    sendThread.stop();
    sendThread.join();
}

BlockingQueue<std::shared_ptr<Message>>* Client::getQueue(){
    return &sendQueue;
}

Client::Client(const char *host, const char *service, bool mute)
            : proxy(host, service), _board(false), gameFinished(false), mute(mute) {
    std::unique_ptr<Scene> configScene = std::make_unique<ConfigScene>();
    sceneManager.addScene(std::make_unique<LoginScene>(configScene.get(), name, gameFinished), LOGIN_SCENE);
    sceneManager.addScene(std::make_unique<LobbyScene>(configScene.get(), &playerType, &roomId, gameFinished), LOBBY_SCENE);
    sceneManager.addScene(std::move(configScene), CONFIG_SCENE);
}

