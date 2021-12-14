#ifndef QUANTUM_CHESS_ENTITY_H
#define QUANTUM_CHESS_ENTITY_H

#include <SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

class Entity {
protected:
    SDL2pp::Texture _texture;
    SDL2pp::Rect _rect;
    SDL_Color _color;
public:
    Entity(SDL2pp::Texture &&texture, const SDL2pp::Rect &rect, SDL_Color color = {255, 255, 255, 255});

    void updateTexture(SDL2pp::Texture &&texture);

    virtual void render(SDL2pp::Renderer *renderer, const int alpha);
};


#endif //QUANTUM_CHESS_ENTITY_H
