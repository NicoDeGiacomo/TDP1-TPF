#include "Login.h"
#include <SDL2pp/SDL2pp.hh>

Login::Login(SDL2pp::Renderer &renderer) : renderer(renderer) {}

void Login::start() {
    // Main loop
	while (1) {
		// Event processing:
		// - If window is closed, or Q or Escape buttons are pressed,
		//   quit the application
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return;
			} else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE: case SDLK_q:
					return;
				}
			}
		}

		// Clear screen
		renderer.Clear();

        std::string title = "Welcome to Quantum Chess";
        this->insert_title(title);

		// Show rendered frame
		renderer.Present();

		// Frame limiter: sleep for a little bit to not eat 100% of CPU
		SDL_Delay(1);
	}
}

void Login::insert_title(std::string &text) {
    // Initialize SDL_ttf library
	SDL2pp::SDLTTF ttf;

    // Load font, 12pt size
	SDL2pp::Font font("../assets/fonts/Vera.ttf", 30);

    // Render the text into new texture. Note that SDL_ttf render
    // text into Surface, which is converted into texture on the fly
    SDL2pp::Texture text_sprite(
            renderer,
            font.RenderText_Blended(text, SDL_Color{255, 255, 255, 255})
        );

    int y_text_pos = renderer.GetOutputHeight() * 0.2;
    int x_text_pos = renderer.GetOutputWidth() * 0.5 - text_sprite.GetWidth() * 0.5;

    // Copy texture into top-left corner of the window
    renderer.Copy(text_sprite, 
                SDL2pp::NullOpt, 
                SDL2pp::Rect(x_text_pos, y_text_pos, 
                            text_sprite.GetWidth(), text_sprite.GetHeight()));

}
