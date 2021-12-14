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
#include "StageMode.h"

int main(int argc, const char *argv[]) {
    StageMode::log("STARTING CLIENT");
    bool mute = false;
    if (argc > 1 && !strcmp(argv[1], "-m")) mute = true;

    try {
        Client client("localhost", "7777", mute);
        client.run();
    } catch(const std::exception &e) {
        std::cerr << "Se atrapó una excepcion en el cliente: '" 
                  << e.what() << "'" << std::endl;
        return 2;
    } catch(...) {
        std::cerr << "Error desconocido en el cliente" << std::endl;
        return 2;
    }

    return 0;
}