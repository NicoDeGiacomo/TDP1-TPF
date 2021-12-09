#include <unistd.h>
#include <Window.hh>
#include <SDL.hh>
#include <SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL_image.h>
#include <cstdio>
#include <Renderer.cc>

#include "Socket.h"
#include <iostream>
#include <vector>
#include <thread>
#include "Client.h"
#include "LoginScene.h"
#include "GameScene.h"

void close_client() {
    std::cout << "closing client" << std::endl;
}


int main(int argc, const char *argv[]) {
    printf("STARTING CLIENT\n");

    /////////////////////////////////
    /// Testing board window, you can comment this block if you want (640x480 hardcoded)
    //Board board;
    //Client client(argv[1], argv[2], board);
    //GameScene mainGameScreen(renderer, &board, client.getQueue());
    // run thread
    //mainGameScreen.start();
    //std::cin.get(); //any key to continue
    //mainGameScreen.join();
    /////////////////////////////////


    /*LoginScene login(renderer);
    login.start();
    std::string user_name = login.get_user_name();

    std::cout << "USERNAME: " << user_name << "\n";
    GameLobby gameLobby(renderer, user_name);


    if (gameLobby.start() == 1) {
        close_client();
        return 0;
    }*/
    
    //TODO: need to encapsulate the chat
    //create the room class
    //handle the logic for client joining or leaving the room
    // Client client;
    // client.start();
    // board()
    // close_client();

    // refreshScreen
    // click -> move -> .......
    // refreshScreen

    if (argc != 3) {
        std::cerr << "Error en la cantidad de argumentos\n"
        << "El cliente se ejecuta de la siguiente manera:\n"
        << "./client <host> <service>\n";
        return 1;
    }

    try {
        Client client(argv[1], argv[2]);
        client.run();
        close_client();
    } catch(const std::exception &e) {
        std::cerr << "Se atrapó una excepcion en el cliente: '" 
                  << e.what() << "'" << std::endl;
        return 2;
    } catch(...) {
        std::cerr << "Error desconocido en el cliente" << std::endl;
        return 2;
    }

    //mainGameScreen.join();
    return 0;
}