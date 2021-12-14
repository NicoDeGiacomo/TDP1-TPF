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
        StageMode::log(
                    std::string("Exception caught in client: '") + e.what()
                        + "'");
        return 1;
    } catch(...) {
        StageMode::log("Unknown error caught in client.");
        return 2;
    }

    return 0;
}