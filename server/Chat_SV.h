//
// Created by ale on 9/11/2021.
//

#ifndef QUANTUM_CHESS_CHAT_SV_H
#define QUANTUM_CHESS_CHAT_SV_H
#include "ProtectedString.h"
#include "Socket.h"
#include <list>
#include <thread>

class Chat_SV {
private:
    ProtectedString protectedString;
    std::list<Socket> listOfPeers;
    std::list<std::thread> receiverThreads;
    std::list<std::thread> senderThreads;
public:
    void start();

    void runReceiverThread(Socket* peer, ProtectedString* pString);

    void runSenderThread(std::list<Socket>* sockets, ProtectedString *pString);

    void joinAllThreads();
};


#endif //QUANTUM_CHESS_CHAT_SV_H
