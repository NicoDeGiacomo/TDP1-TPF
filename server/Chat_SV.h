//
// Created by ale on 9/11/2021.
//

#ifndef QUANTUM_CHESS_CHAT_SV_H
#define QUANTUM_CHESS_CHAT_SV_H
#include "ProtectedString.h"
#include <Socket.h>

class Chat_SV {

public:
    void start();

    void runReceiverThread(int peer, ProtectedString* pString);

    void runSenderThread(std::list<Socket> *sockets, ProtectedString *pString);
};


#endif //QUANTUM_CHESS_CHAT_SV_H
