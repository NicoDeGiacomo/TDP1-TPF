#include "SendThread.h"
#include "Socket.h"
#include "Protocol.h"
#include <iostream>

/***********************
    Metodos protegidos
************************/

void SendThread::run() {
    std::string input;
    std::cout << "Running SendThread\n";
    while (keep_talking) {
        /*input = "";
        std::getline(std::cin, input);
        if (input.empty()) {
            break;
        }*/
        try {
            std::cout << "Sending " << "\n";
            std::shared_ptr<Message> msg = this->sendQueue.top();
            this->sendQueue.pop();
            //std::cout << "Sending: " << input << "\n";
            //std::shared_ptr<Message> msg = Protocol::StringToMessage(input, this->id);
            msg->apply(board, chat);
            proxy.send(msg);
            std::cout << "sent " << "\n";
        } catch (ClosedSocketException& e) {
            //TODO: for some reason this catch isnt catching, the socket
            //is throwing the error receiving bytes exception instead
            // std::cout << e.what() << std::endl;
            this->stop();
        } catch (ClosedQueueException& e){
            this->stop();
        } catch(const std::exception &e) {
            this->stop();
            std::cerr << "Exception caught in SendThread: '" 
                    << e.what() << "'" << std::endl;
        } catch(...) {
            std::cerr << "Unknown error caught in SendThread" << std::endl;
            // return;
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
