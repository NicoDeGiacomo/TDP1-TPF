//
// Created by ale on 12/11/21.
//

#include <iostream>
#include <ChatMessage.h>
#include "Player.h"
#include "Protocol.h"

void Player::send(const Message& message) const {
    std::string string = Protocol::MessageToString(message);
    // double dispatch
    // message.getId() != this.id
    this->socket.send(string.c_str(), string.length());
}

bool Player::isVacant() const {
    return this->socket.isNotActive();
}

void Player::initPlayer(Socket &&connectedSocket, BlockingQueue<std::unique_ptr<Message>> *queue , BlockingQueue<Message> *thisSenderQueueIsJustForDebugging) {
    this->socket = std::move(connectedSocket);
    this->queueOfReceived = queue;
    this->_thisSenderQueueIsJustForDebugging = thisSenderQueueIsJustForDebugging;
}

Player::Player(Socket&& socket, BlockingQueue<std::unique_ptr<Message>> *queue , BlockingQueue<Message> *thisSenderQueueIsJustForDebugging) {
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
        std::cout << std::endl;
        std::string buffer(received, received + 4);
        std::unique_ptr<Message> message = Protocol::StringToMessage(buffer, this.id);
        std::string bufferfordebugging = message->getMessage();
        this->queueOfReceived->produce(std::move(message));

        //TODO: remove this, is just for debugging
        //after server receives message from a client, it loads it in the sender queue
        //but it needs to first be processed
        //using ChatMessage instead of Message for testing inheritance, its the same thing for now
        ChatMessage bufferMessageForDebugging(bufferfordebugging);
        this->_thisSenderQueueIsJustForDebugging->produce(std::move(bufferMessageForDebugging));
        std::cout << std::endl << "---" << std::endl;
    }
}

void Player::join() {
    if (this->receiverThread.joinable())
        this->receiverThread.join();
}

Player::Player() {
}

Player::~Player() {
    //could join by force here, and make join private
    //std::cout << "joining player by destructor" << std::endl;
    //this->join();
}
