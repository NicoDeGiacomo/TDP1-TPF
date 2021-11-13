//
// Created by ale on 12/11/21.
//

#include <iostream>
#include "Player.h"
//TODO: player va a recibir MESSAGE en vez de (buffer y size), en send y recv
void Player::receive(char *buffer, int size) {
    //conoce al pprotocolo, devuelve un MESSAGE
    this->socket.receive(buffer, size);
}

void Player::send(const char *string, int size) {
    this->socket.send(string, size);
}

bool Player::isVacant() {
    return this->socket.isNotActive();
}

void Player::initPlayer(Socket &&connectedSocket, BlockingQueue<std::string> *queue) {
    this->socket = std::move(connectedSocket);
    this->queueOfReceived = queue;
}

Player::Player(Socket&& socket, BlockingQueue<std::string> *queue) {
    this->socket = std::move(socket);
    this->queueOfReceived = queue;
}

void Player::startReceivingMessages() {
    this->receiverThread = std::thread(&Player::runReceiverThread, this);
}

void Player::runReceiverThread(){
    std::cout << "running receiver sv thread" << std::endl;
    while (true) {
        //TODO: remove this 4 hardcoded, need to add protocol
        char received[4];
        try {
            socket.receive(received, 4);
        } catch (ClosedSocketException& e){
            std::cout << e.what() << std::endl;
            return;
        }
        std::cout << "--server received" << std::endl;
        //Message* msg = Protocol::getMessageFromBytes(received);
        for (auto &c : received){
            std::cout << c;
        }
        std::string buffer(received, received + 4);
        this->queueOfReceived->produce(std::move(buffer));
        std::cout << std::endl << "---" << std::endl;
    }
}

void Player::join() {
    this->receiverThread.join();
}

Player::Player() {
}
