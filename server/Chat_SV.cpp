//
// Created by ale on 9/11/2021.
//

#include <iostream>
#include <thread>
#include <ProtectedString.h>
#include <list>
#include "Chat_SV.h"

void Chat_SV::start() {
    Socket acceptor;
    acceptor.bind("7777");
    acceptor.listen(6);


    //TODO: need to look for dead threads and shutdown everything after finish chat.
    //TODO: remove this placeholder variable, move this accept to a ROOM or another class
    int i = 0;
    while (true && i != 2){
        Socket peer = acceptor.accept();
        if (peer.isNotActive())
            //proceed to clean and shutdown threads
            break;
        std::cout << "valid socket accepted" << std::endl;
        this->listOfPeers.push_front(std::move(peer));
        this->senderThreads.push_front(
                std::thread(&Chat_SV::runSenderThread,
                            this,
                            &this->listOfPeers,
                            &this->protectedString));
        this->receiverThreads.push_front(
                std::thread(&Chat_SV::runReceiverThread,
                            this,
                            &this->listOfPeers.front(),
                            &this->protectedString));

        //this->deleteDeadWorkers();
        i++;
    }
    this->joinAllThreads();

    //std::thread receiver, sender;
    //std::list<Socket> sockets;
    //sockets.push_front(std::move(peer));
    //receiver = std::thread(&Chat_SV::runReceiverThread, this, &sockets.front(), &pString);
    //sender = std::thread(&Chat_SV::runSenderThread, this, &sockets, &pString);
    //receiver.join();
    //sender.join();

}

void Chat_SV::runReceiverThread(Socket* peer, ProtectedString* pString){
    std::cout << "running receiver sv thread" << std::endl;
    while (true) {
        //TODO: remove this 4 hardcoded, need to add protocol
        char received[4];
        try {
            peer->receive(received, 4);
        } catch (ClosedSocketException& e){
            std::cout << e.what() << std::endl;
            return;
        }
        std::cout << "--server received" << std::endl;
        for (auto &c : received){
            std::cout << c;
        }
        std::string buffer(received, received + 4);
        pString->addString(std::move(buffer));
        std::cout << std::endl << "---" << std::endl;
    }
}

void Chat_SV::runSenderThread(std::list<Socket>* sockets, ProtectedString* pString){
    std::cout << "running sender sv thread" << std::endl;
    while (true) {
        std::string toSend;
        pString->getStringIfNotEmpty(toSend);
        try {
            for (auto &socket: *sockets) {
                socket.send(toSend.c_str(), toSend.length());
            }
        } catch (ClosedSocketException& e){
            //TODO: for some reason this catch isnt catching, the socket
            //is throwing the error receiving bytes exception instead
            std::cout << e.what() << std::endl;
            return;
        }
        std::cout << "-server just sent: " << toSend << std::endl;
    }
}

void Chat_SV::joinAllThreads() {
    for(auto & t : receiverThreads)
        t.join();
    for(auto & t : senderThreads)
        t.join();
    std::cout << "all threads joined" << std::endl;
}
