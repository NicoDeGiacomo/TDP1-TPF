#include "Screen.h"

Screen::Screen(SDL2pp::Renderer &renderer) : renderer(renderer) {}

void Screen::insert_text(std::string &text, 
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
            renderer,
            font.RenderText_Blended(text, SDL_Color{255, 255, 255, 255})
        );

    int x_text_pos = 0;
    int y_text_pos = 0;

    switch (flags)
    {
    case A_CENTER:
        x_text_pos = renderer.GetOutputWidth() * pos_x / 100 - text_sprite.GetWidth() * 0.5;
        y_text_pos = renderer.GetOutputHeight() * pos_y / 100;
        break;
    case A_RIGHT:
        x_text_pos = renderer.GetOutputWidth() - pos_x - text_sprite.GetWidth();
        y_text_pos = pos_y;
        break;
    default: // A_LEFT
        x_text_pos = pos_x;
        y_text_pos = pos_y;
        break;
    }

    // Copy texture into top-left corner of the window
    renderer.Copy(text_sprite, 
                SDL2pp::NullOpt, 
                SDL2pp::Rect(x_text_pos, y_text_pos, 
                            text_sprite.GetWidth(), text_sprite.GetHeight()));
}
