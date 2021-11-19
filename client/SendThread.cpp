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
            proxy.send(Protocol::StringToMessage(input, id));
        } catch (ClosedSocketException& e){
            //TODO: for some reason this catch isnt catching, the socket
            //is throwing the error receiving bytes exception instead
            std::cout << e.what() << std::endl;
            return;
        } catch(...) {
            std::cerr << "Unknown error caught in SendThread" << std::endl;
            return;
        }
    }
}

/***********************
    Metodos publicos
************************/

SendThread::SendThread(ServerProxy &proxy, int id)
                : proxy(proxy),
                  id(id),
                  keep_talking(true) {}

void SendThread::stop() {
    this->keep_talking = false;
    // this->proxy.close_connection();
}
