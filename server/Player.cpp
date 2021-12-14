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
    proxy.close_connection();
    recvThread.stop();
    recvThread.join();
}

bool Player::isDead() const {
    return this->proxy.isClosed();
}

int Player::getId() {
    return proxy.getId();
}
