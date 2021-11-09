#include "Login.h"
#include <SDL2pp/SDL2pp.hh>

Login::Login(SDL2pp::Renderer &renderer) : renderer(renderer) {}

void Login::start() {
	
	SDL_bool done = SDL_FALSE;

    SDL_StartTextInput();
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
	SDL_StopTextInput();
}

void Login::redraw() {
	// Clear screen
	renderer.Clear();

	std::string title = "Welcome to Quantum Chess";
	this->insert_text(title, 30, 50, 20);
	std::string choose_text("Please choose a username:");
	this->insert_text(choose_text, 20, 50, 40);
	this->insert_text(this->user_name, 20, 50, 50);

	// Show rendered frame
	renderer.Present();
}

void Login::insert_text(std::string &text, 
						int font_size, 
						int rel_pos_x, 
						int rel_pos_y) {
    if (text.empty()) return;
	// Initialize SDL_ttf library
	SDL2pp::SDLTTF ttf;

    // Load font, 12pt size
	SDL2pp::Font font("../assets/fonts/Vera.ttf", font_size);

    // Render the text into new texture. Note that SDL_ttf render
    // text into Surface, which is converted into texture on the fly
    SDL2pp::Texture text_sprite(
            renderer,
            font.RenderText_Blended(text, SDL_Color{255, 255, 255, 255})
        );

    int x_text_pos = renderer.GetOutputWidth() * rel_pos_x / 100 - text_sprite.GetWidth() * 0.5;
    int y_text_pos = renderer.GetOutputHeight() * rel_pos_y / 100;

    // Copy texture into top-left corner of the window
    renderer.Copy(text_sprite, 
                SDL2pp::NullOpt, 
                SDL2pp::Rect(x_text_pos, y_text_pos, 
                            text_sprite.GetWidth(), text_sprite.GetHeight()));
}

std::string Login::get_user_name() {
	return this->user_name;
}
