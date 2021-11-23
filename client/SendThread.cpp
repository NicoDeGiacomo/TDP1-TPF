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
        input = "";
        std::getline(std::cin, input);
        if (input.empty()) {
            break;
        }
        try {
            std::cout << "Sending: " << input << "\n";
            std::shared_ptr<Message> msg = Protocol::StringToMessage(input, this->id);
            msg->apply(board);
            proxy.send(msg);
        } catch (ClosedSocketException& e){
            //TODO: for some reason this catch isnt catching, the socket
            //is throwing the error receiving bytes exception instead
            std::cout << e.what() << std::endl;
            return;
        } catch(const std::exception &e) {
            std::cerr << "Exception caught in SendThread: '" 
                    << e.what() << "'" << std::endl;
        } catch(...) {
            std::cerr << "Unknown error caught in SendThread" << std::endl;
            return;
        }
    }
}

/***********************
    Metodos publicos
************************/

SendThread::SendThread(ServerProxy &proxy, Board &board, int id)
                : proxy(proxy),
                  board(board),
                  id(id),
                  keep_talking(true) {}

void SendThread::stop() {
    this->keep_talking = false;
    // this->proxy.close_connection();
}
