//
// Created by ale on 7/12/21.
//

#ifndef QUANTUM_CHESS_BUTTONTEMP_H
#define QUANTUM_CHESS_BUTTONTEMP_H


#include <SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

class ButtonTEMP {
private:
    SDL2pp::Texture _texture;
    SDL2pp::Rect _rect;
    std::function<void()> _handler{};
public:
    ButtonTEMP(SDL2pp::Texture &&texture, const SDL2pp::Rect &rect);

    void onClick(std::function<void()>&& handler);

    void click();

    void render(SDL2pp::Renderer *renderer, const int alpha);

    bool contains(int x, int y);
};


#endif //QUANTUM_CHESS_BUTTONTEMP_H
