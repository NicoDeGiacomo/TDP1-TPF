#include "SendThread.h"
#include "Socket.h"
#include "Protocol.h"
#include "StageMode.h"
#include <iostream>

/***********************
    Metodos protegidos
************************/

void SendThread::run() {
    std::string input;
    StageMode::log("Running SendThread");
    while (keep_talking) {
        try {
            std::shared_ptr<Message> msg = this->sendQueue.top();
            this->sendQueue.pop();
            msg->apply(board, chat);
            proxy.send(msg);
        } catch (ClosedSocketException& e) {
            this->stop();
        } catch (ClosedQueueException& e){
            this->stop();
        } catch(const std::exception &e) {
            std::cerr << "Exception caught in SendThread: '" 
                    << e.what() << "'" << std::endl;
        } catch(...) {
            std::cerr << "Unknown error caught in SendThread" << std::endl;
        }
    }
}

/***********************
    Metodos publicos
************************/

SendThread::SendThread(ServerProxy &proxy, Board &board, Chat &chat, 
                BlockingQueue<std::shared_ptr<Message>> &sendQueue)
                : proxy(proxy),
                  board(board),
                  chat(chat),
                  keep_talking(true),
                  sendQueue(sendQueue) {}

void SendThread::stop() {
    this->keep_talking = false;
    this->sendQueue.close();
    this->proxy.close_connection();
    std::cout << "Closing SendThread" << std::endl;
}
