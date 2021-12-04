//
// Created by ale on 12/11/21.
//

#include <iostream>
#include <messages/ChatMessage.h>
#include "Player.h"
#include "Protocol.h"
#include "RecvThread.h"

Player::Player(BlockingQueue<std::shared_ptr<Message>> &queue)
                 : queueOfReceived(queue), recvThread(proxy, queue) {}

Player::Player(Socket &socket, 
              BlockingQueue<std::shared_ptr<Message>> &queue, 
              int id, 
              char type,
               unsigned int seed)
              : proxy(socket, id, type, seed),
              queueOfReceived(queue), 
              recvThread(proxy, queue), 
              id(id) {}

void Player::initPlayer(Socket &connectedSocket, int id, char type, unsigned int seed) {
    proxy.initProxy(connectedSocket, id, type, seed);
    this->id = id;
}

void Player::send(const std::shared_ptr<Message>& message) const {
    if (message == nullptr) {
        return;
    }

    std::string string = Protocol::MessageToString(message);
    // double dispatch
    // message.getId() != this.id
    // this->socket.send(string.c_str(), string.length());
    proxy.send(message);
}

bool Player::isVacant() const {
    return proxy.isNotActive();
}

void Player::startReceivingMessages() {
    recvThread.start();
    // this->receiverThread = std::thread(&Player::runReceiverThread, this);
}

void Player::join() {
    // if (this->receiverThread.joinable())
    //     this->receiverThread.join();
}


Player::~Player() {
    //could join by force here, and make join private
    //std::cout << "joining player by destructor" << std::endl;
    //this->join();
}
