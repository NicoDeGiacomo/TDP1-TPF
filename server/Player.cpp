//
// Created by ale on 12/11/21.
//

#include <iostream>
#include <messages/ChatMessage.h>
#include "Player.h"
#include "Protocol.h"

void Player::send(const std::shared_ptr<Message>& message) const {
    std::string string = Protocol::MessageToString(message);
    // double dispatch
    // message.getId() != this.id
    this->socket.send(string.c_str(), string.length());
}

bool Player::isVacant() const {
    return this->socket.isNotActive();
}

void Player::initPlayer(Socket &&connectedSocket, BlockingQueue<std::shared_ptr<Message>> *queue) {
    this->socket = std::move(connectedSocket);
    this->queueOfReceived = queue;
}

Player::Player(Socket&& socket, BlockingQueue<std::shared_ptr<Message>> *queue) {
    this->socket = std::move(socket);
    this->queueOfReceived = queue;
}

void Player::startReceivingMessages() {
    this->receiverThread = std::thread(&Player::runReceiverThread, this);
}

void Player::runReceiverThread(){
    std::cout << "running receiver sv thread" << std::endl;
    while (true) {
        char received[6];
        try {
            socket.receive(received, 6);
        } catch (ClosedSocketException& e){
            std::cout << e.what() << std::endl;
            return;
        }
        std::cout << "--server received" << std::endl;
        //Message* msg = Protocol::getMessageFromBytes(received);
        for (auto &c : received){
            std::cout << c;
        }
        std::cout << std::endl;
        std::string buffer(received, received + 6);
        std::shared_ptr<Message> message = Protocol::StringToMessage(buffer, this->id);
        this->queueOfReceived->produce(std::move(message));
        std::cout << std::endl << "---" << std::endl;
    }
}

void Player::join() {
    if (this->receiverThread.joinable())
        this->receiverThread.join();
}

Player::Player() {
    this->id = "placeholder id";
}

Player::~Player() {
    //could join by force here, and make join private
    //std::cout << "joining player by destructor" << std::endl;
    //this->join();
}
