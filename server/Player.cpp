//
// Created by ale on 12/11/21.
//

#include <iostream>
#include "Player.h"
#include "Protocol.h"

//TODO: player va a recibir MESSAGE en vez de (buffer y size), en send y recv
void Player::send(const Message& message) const {
    std::string string = Protocol::MessageToString(message);
    this->socket.send(string.c_str(), string.length());
}

bool Player::isVacant() const {
    return this->socket.isNotActive();
}

void Player::initPlayer(Socket &&connectedSocket, BlockingQueue<Message> *queue , BlockingQueue<Message> *thisSenderQueueIsJustForDebugging) {
    this->socket = std::move(connectedSocket);
    this->queueOfReceived = queue;
    this->_thisSenderQueueIsJustForDebugging = thisSenderQueueIsJustForDebugging;
}

Player::Player(Socket&& socket, BlockingQueue<Message> *queue , BlockingQueue<Message> *thisSenderQueueIsJustForDebugging) {
    this->socket = std::move(socket);
    this->queueOfReceived = queue;
    this->_thisSenderQueueIsJustForDebugging = thisSenderQueueIsJustForDebugging;
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
        Message message = Protocol::StringToMessage(buffer);
        this->queueOfReceived->produce(message);

        //TODO: remove this, is just for debugging
        //after server receives message from a client, it loads it in the sender queue
        //but it needs to first be processed
        this->_thisSenderQueueIsJustForDebugging->produce(message);
        std::cout << std::endl << "---" << std::endl;
    }
}

void Player::join() {
    this->receiverThread.join();
}

Player::Player() {
}
