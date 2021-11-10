//
// Created by ale on 9/11/2021.
//

#include <string>
#include <iostream>
#include <Socket.h>
#include <thread>
#include "Chat_CL.h"
#include "ProtectedString.h"

void Chat_CL::start() {
    Socket client;
    client.connect("localhost", "7777");
    std::thread sender, receiver;
    sender = std::thread(&Chat_CL::runSenderThread, this, &client);
    receiver = std::thread(&Chat_CL::runReceiverThread, this, &client);
    sender.join();
    receiver.join();
}

void Chat_CL::runReceiverThread(Socket* client){
    while (true) {
        //TODO: remove this 4 hardcoded, need to add protocol
        char received[4];
        try {
            client->receive(received, 4);
        } catch (ClosedSocketException& e){
            std::cout << e.what() << std::endl;
            return;
        }
        std::cout << "--client received" << std::endl;
        for (auto &c : received){
            std::cout << c;
        }
        std::cout << std::endl << "---" << std::endl;
    }
}

void Chat_CL::runSenderThread(Socket* client){
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

