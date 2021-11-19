#include "RecvThread.h"
#include "Message.h"
#include "Protocol.h"
#include <iostream>


/***********************
    Metodos protegidos
************************/

void RecvThread::run() {
    std::cout << "Running RecvThread\n";
    // while (keep_talking) {
    //     //TODO: remove this 6 hardcoded, need to add protocol
    //     char received[6];
    //     try {
    //         socket.receive(received, 6);
    //     } catch (ClosedSocketException& e){
    //         std::cout << e.what() << std::endl;
    //         return;
    //     }
    //     std::cout << "--client received" << std::endl;
    //     for (auto &c : received){
    //         std::cout << c;
    //     }

    //     std::string buffer(received, received + 6);
    //     std::shared_ptr<Message> message = Protocol::StringToMessage(buffer, this->id);
    //     // std::cout << std::endl << "---" << std::endl;
    //     // message->apply(this->board);
    //     queue.produce(std::move(message));

    // }

    while (keep_talking) {
        std::shared_ptr<Message> message = proxy.recv();
        queue.produce(std::move(message));
    }
}

/***********************
    Metodos publicos
************************/

RecvThread::RecvThread(ServerProxy &proxy, BlockingQueue<std::shared_ptr<Message>> &queue) 
                    : proxy(proxy), queue(queue), keep_talking(true) {}

void RecvThread::stop() {
    this->keep_talking = false;
    // this->proxy.close_connection();
}
