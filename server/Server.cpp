#include <Server.h>
#include <RoomManager.h>
#include <iostream>

#define QUIT_CHAR 'q'

/***********************
    Metodos publicos
************************/

Server::Server(const std::string service) : service(service) {}

void Server::run() {
    RoomManager roomManager(service);
    roomManager.start();
    char c = getchar();
    while (c != QUIT_CHAR) {
        c = std::cin.get();
    }
    roomManager.stop();
    roomManager.join();
}
