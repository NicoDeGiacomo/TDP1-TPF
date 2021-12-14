#ifndef QUANTUM_CHESS_CLICKABLEENTITY_H
#define QUANTUM_CHESS_CLICKABLEENTITY_H


#include <SDL_image.h>
#include <SDL2pp/SDL2pp.hh>
#include "Entity.h"

class ClickableEntity : public Entity {
private:
    std::function<void()> _handler{};
public:
    ClickableEntity(SDL2pp::Texture &&texture, const SDL2pp::Rect &rect, SDL_Color color = {255, 255, 255, 255});

    void onClick(std::function<void()>&& handler);

    void click();

    bool contains(int x, int y);

    void render(SDL2pp::Renderer *renderer, const int alpha) override;
};


#endif //QUANTUM_CHESS_CLICKABLEENTITY_H
