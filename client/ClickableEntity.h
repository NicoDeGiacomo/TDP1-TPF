//
// Created by ale on 7/12/21.
//

#ifndef QUANTUM_CHESS_CLICKABLEENTITY_H
#define QUANTUM_CHESS_CLICKABLEENTITY_H


#include <SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

class ClickableEntity {
private:
    SDL2pp::Texture _texture;
    SDL2pp::Rect _rect;
    std::function<void()> _handler{};
    SDL_Color _color;
public:
    ClickableEntity(SDL2pp::Texture &&texture, const SDL2pp::Rect &rect, SDL_Color color = {255, 255, 255, 255});

    void updateTexture(SDL2pp::Texture &&texture);

    void onClick(std::function<void()>&& handler);

    void click();

    void render(SDL2pp::Renderer *renderer, const int alpha);

    bool contains(int x, int y);
};


#endif //QUANTUM_CHESS_CLICKABLEENTITY_H
