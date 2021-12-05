#include "LoginScene.h"
#include "Screen.h"
#include <SDL2pp/SDL2pp.hh>

/*LoginScene::LoginScene(SDL2pp::Renderer* renderer) {
	_renderer = renderer;
}*/

void LoginScene::updateLoop() {
	
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
        render();

        SDL_Delay(1000/60); //todo: should ask for monitor refresh rate, this is capped at 60fps
    }
}

void LoginScene::render() {
	// Clear screen
	_renderer->Clear();

	std::string title = "Welcome to Quantum Chess";
	this->insert_text(title, 30, 50, 20, A_CENTER);
	std::string choose_text("Please choose a username:");
	this->insert_text(choose_text, 20, 50, 40, A_CENTER);
	this->insert_text(this->user_name, 20, 50, 50, A_CENTER);

	// Show rendered frame
	_renderer->Present();
}

std::string LoginScene::get_user_name() {
	return this->user_name;
}

LoginScene::LoginScene() {

}

void LoginScene::insert_text(std::string &text,
                             int font_size,
                             int pos_x,
                             int pos_y,
                             int flags) {
	if (text.empty()) return;
	// Initialize SDL_ttf library
	SDL2pp::SDLTTF ttf;

	// Load font, 12pt size
	SDL2pp::Font font("../assets/fonts/Vera.ttf", font_size);

	// Render the text into new texture. Note that SDL_ttf render
	// text into Surface, which is converted into texture on the fly
	SDL2pp::Texture text_sprite(
			(*_renderer),
			font.RenderText_Blended(text, SDL_Color{255, 255, 255, 255})
	);

	int x_text_pos = 0;
	int y_text_pos = 0;

	switch (flags)
	{
		case A_CENTER:
			x_text_pos = _renderer->GetOutputWidth() * pos_x / 100 - text_sprite.GetWidth() * 0.5;
			y_text_pos = _renderer->GetOutputHeight() * pos_y / 100;
			break;
		case A_RIGHT:
			x_text_pos = _renderer->GetOutputWidth() - pos_x - text_sprite.GetWidth();
			y_text_pos = pos_y;
			break;
		default: // A_LEFT
			x_text_pos = pos_x;
			y_text_pos = pos_y;
			break;
	}

	// Copy texture into top-left corner of the window
	_renderer->Copy(text_sprite,
				  SDL2pp::NullOpt,
				  SDL2pp::Rect(x_text_pos, y_text_pos,
							   text_sprite.GetWidth(), text_sprite.GetHeight()));
}

void LoginScene::load(SDL2pp::Renderer *renderer) {
    Scene::load(renderer);
    //load scene, but dont process input nor render textures
}
