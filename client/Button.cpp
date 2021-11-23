#include "Button.h"

Button::Button(SDL2pp::Renderer &renderer,
                std::string &text, 
				int font_size, 
				int pos_x, 
				int pos_y,
                int flags) 
                : renderer(renderer), 
                  text(text),
                  font_size(font_size),
                  pos_x(pos_x),
                  pos_y(pos_y),
                  flags(flags) {
    
}

void Button::click(SDL_MouseButtonEvent& b) {
    bool x_range = x_text_pos < b.x && b.x < x_text_pos + text_width;
    bool y_range = y_text_pos < b.y && b.y < y_text_pos + text_height;
    if (b.button == SDL_BUTTON_LEFT && x_range && y_range) {
		std::cout << "LEFT CLICK on " << text << "\n";
	}
}

void Button::redraw() {
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

    text_width = text_sprite.GetWidth();
    text_height = text_sprite.GetHeight();

    switch (flags) {
        case A_CENTER:
            x_text_pos = renderer.GetOutputWidth() * pos_x / 100 - text_width * 0.5;
            y_text_pos = renderer.GetOutputHeight() * pos_y / 100;
            break;
        case A_RIGHT:
            x_text_pos = renderer.GetOutputWidth() - pos_x - text_width;
            y_text_pos = pos_y;
            break;
        default: // A_LEFT
            x_text_pos = pos_x;
            y_text_pos = pos_y;
            break;
    }

    renderer.Copy(text_sprite,
                  SDL2pp::NullOpt,
                  SDL2pp::Rect(x_text_pos, y_text_pos,text_width, text_height));
}

void Button::onClick(void (*buttonClicked)()) {
    buttonClicked();
}
