#include <unistd.h>
#include <Window.hh>
#include <SDL.hh>
#include <SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <cstdio>

#include "Socket.h"
#include <iostream>
#include <vector>
#include "Chat_CL.h"
#include "Login.h"

int main() {
    printf("STARTING CLIENT\n");
    SDL2pp::SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL2pp::Window window("libSDL2pp demo: fill",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          640,
                          480,
                          SDL_WINDOW_RESIZABLE);

    
    // Create accelerated video renderer with default driver
	SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    Login login(renderer);
    login.start();
    std::string user_name = login.get_user_name();

    std::cout << "USERNAME: " << user_name << "\n";
    
    // sleep(5);
    // //TODO: need to encapsulate the chat
    // //create the room class
    // //handle the logic for client joining or leaving the room
    // Chat_CL chat;
    // chat.start();
    // std::cout << "closing client" << std::endl;
    return 0;
}
