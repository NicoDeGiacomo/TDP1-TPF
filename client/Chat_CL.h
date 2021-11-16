//
// Created by ale on 9/11/2021.
//

#ifndef QUANTUM_CHESS_CHAT_CL_H
#define QUANTUM_CHESS_CHAT_CL_H


class Chat_CL {

public:
    void start();

    void runSenderThread(Socket* client);

    void runReceiverThread(Socket* client);
};


#endif //QUANTUM_CHESS_CHAT_CL_H
