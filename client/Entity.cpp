//
// Created by ale on 13/12/21.
//

#include "Entity.h"
Entity::Entity(SDL2pp::Texture &&texture, const SDL2pp::Rect &rect, SDL_Color color) :
        _texture(std::move(texture)), _rect(rect), _color(color) {}

void Entity::render(SDL2pp::Renderer *renderer, const int alpha) {
    _texture.SetColorAndAlphaMod(_color);
    _texture.SetAlphaMod(alpha);
    renderer->Copy(_texture, SDL2pp::NullOpt, _rect);
}

void Entity::updateTexture(SDL2pp::Texture &&texture) {
    _rect.SetW(texture.GetWidth());
    _texture = std::move(texture);
}
