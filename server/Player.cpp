#include <iostream>
#include <messages/ChatMessage.h>
#include "Player.h"
#include "Protocol.h"
#include "RecvThread.h"

Player::Player(ClientProxy &client, 
              BlockingQueue<std::shared_ptr<Message>> &queue)
              : proxy(std::move(client)),
              queueOfReceived(queue), 
              recvThread(proxy, queue) {
}

void Player::send(const std::shared_ptr<Message>& message) const {
    if (message == nullptr) return;

    proxy.send(message);
}

void Player::startReceivingMessages() {
    recvThread.start();
}

void Player::join() {
    // if (this->receiverThread.joinable())
    //     this->receiverThread.join();
}

int Player::getId() {
    return proxy.getId();
}

Player::~Player() {
    //could join by force here, and make join private
    //std::cout << "joining player by destructor" << std::endl;
    //this->join();
}
