#include "Login.h"
#include "Screen.h"
#include <SDL2pp/SDL2pp.hh>

Login::Login(SDL2pp::Renderer &renderer) : Screen(renderer) {}

int Login::start() {
	
	SDL_bool done = SDL_FALSE;

    while (!done) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
					//Handle backspace
					if( event.key.keysym.sym == SDLK_BACKSPACE && user_name.length() > 0 ) {
						user_name.pop_back();
					}
					//Handle copy
					else if( event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL ) {
						SDL_SetClipboardText( user_name.c_str() );
					}
					//Handle paste
					else if( event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL ) {
						user_name += SDL_GetClipboardText();
					}
					else if (event.key.keysym.scancode == SDL_SCANCODE_RETURN)
						done = SDL_TRUE;
                    break;
				case SDL_QUIT:
                    /* Quit */
                    done = SDL_TRUE;
                    break;
                case SDL_TEXTINPUT:
                    /* Add new text onto the end of our text */
					user_name += event.text.text;
                    break;
            }
        }
        redraw();

		// Frame limiter: sleep for a little bit to not eat 100% of CPU
		SDL_Delay(1);
    }

	return 0;
}

void Login::redraw() {
	// Clear screen
	renderer.Clear();

	std::string title = "Welcome to Quantum Chess";
	this->insert_text(title, 30, 50, 20, A_CENTER);
	std::string choose_text("Please choose a username:");
	this->insert_text(choose_text, 20, 50, 40, A_CENTER);
	this->insert_text(this->user_name, 20, 50, 50, A_CENTER);

	// Show rendered frame
	renderer.Present();
}

std::string Login::get_user_name() {
	return this->user_name;
}
