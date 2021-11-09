#include <unistd.h>
#include <Window.hh>
#include <SDL.hh>
#include <SDL.h>
#include <cstdio>
#include "Socket.h"

int main() {
    printf("STARTING CLIENT\n");

    SDL2pp::SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL2pp::Window window("libSDL2pp demo: fill",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          640,
                          480,
                          SDL_WINDOW_RESIZABLE);

    sleep(5);
    return 0;
}
