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

void Client::start() {
    Socket client;
    client.connect("localhost", "7777");
    std::thread sender, receiver;
    sender = std::thread(&Client::runSenderThread, this, &client);
    receiver = std::thread(&Client::runReceiverThread, this, &client);
    sender.join();
    receiver.join();
}

void Client::runReceiverThread(Socket* client){
    while (true) {
        //TODO: remove this 6 hardcoded, need to add protocol
        char received[6];
        try {
            client->receive(received, 6);
        } catch (ClosedSocketException& e){
            std::cout << e.what() << std::endl;
            return;
        }
        std::cout << "--client received" << std::endl;
        for (auto &c : received){
            std::cout << c;
        }

        std::string buffer(received, received + 6);
        std::shared_ptr<Message> message = Protocol::StringToMessage(buffer, this->id);
        std::cout << std::endl << "---" << std::endl;
        message->apply(this->board);
    }
}

void Client::runSenderThread(Socket* client){
    std::string input;
    while (true) {
        input = "";
        std::getline(std::cin, input);
        if (input.empty()) {
            break;
        }
        try {
            client->send(input.c_str(), input.length());
        } catch (ClosedSocketException& e){
            //TODO: for some reason this catch isnt catching, the socket
            //is throwing the error receiving bytes exception instead
            std::cout << e.what() << std::endl;
            return;
        }
        std::cout << "-client just sent: " << input << std::endl;
    }
}

Client::Client() {
    this->id = "123asd";
}

