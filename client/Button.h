#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <SDL2pp/SDL2pp.hh>

#define A_CENTER 0
#define A_LEFT 1
#define A_RIGHT 2

class Button {
public:
    Button(SDL2pp::Renderer &renderer,
           std::string &text, 
		   int font_size, 
		   int pos_x, 
		   int pos_y,
           int flags);
    void redraw();
    void click(SDL_MouseButtonEvent& b);
private:
    SDL2pp::Renderer &renderer;
    std::string text;
    const int font_size;
    const int pos_x;
    const int pos_y;
    const int flags;
    int x_text_pos;
    int y_text_pos;
    int text_width;
    int text_height;
};

#endif  // _GAME_LOBBY_H_
