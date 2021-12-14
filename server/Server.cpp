#include <Server.h>
#include <RoomManager.h>
#include <iostream>

#define LISTEN_BACKLOG 50
#define QUIT_CHAR 'q'

/***********************
    Metodos publicos
************************/

Server::Server(const char *service) {
    this->acceptor.bind(service);
    this->acceptor.listen(LISTEN_BACKLOG);
}

void Server::run() {
    RoomManager roomManager(this->acceptor);
    roomManager.start();
    char c = getchar();
    while (c != QUIT_CHAR) {
        c = std::cin.get();
    }
    roomManager.stop();
    roomManager.join();
}
