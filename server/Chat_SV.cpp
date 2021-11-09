//
// Created by ale on 9/11/2021.
//

#include <Socket.h>
#include <iostream>
#include <thread>
#include <ProtectedString.h>
#include <list>
#include "Chat_SV.h"

void Chat_SV::start() {
    Socket acceptor;
    acceptor.bind("7777");
    acceptor.listen(1);

    //TODO: need to add the accept peer loop, look for dead threads and shutdown everything after finish chat.
    //TODO: big issue by needing two copies of same socket im accessing private file descriptor
    Socket peer = acceptor.accept();
    std::thread receiver, sender;
    ProtectedString pString;
    receiver = std::thread(&Chat_SV::runReceiverThread, this, peer.fd, &pString);
    std::list<Socket> sockets;
    sockets.push_front(std::move(peer));
    sender = std::thread(&Chat_SV::runSenderThread, this, &sockets, &pString);
    receiver.join();
    sender.join();

}

void Chat_SV::runReceiverThread(int fd, ProtectedString* pString){
    Socket peer(fd);
    while (true) {
        //TODO: remove this 4 hardcoded, need to add protocol
        char received[4];
        try {
            peer.receive(received, 4);
        } catch (ClosedSocketException& e){
            //TODO: for some reason this catch isnt catching, the socket
            //is throwing the error receiving bytes exception instead
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