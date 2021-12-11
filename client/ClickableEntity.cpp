//
// Created by ale on 7/12/21.
//

#include "ClickableEntity.h"

ClickableEntity::ClickableEntity(SDL2pp::Texture &&texture, const SDL2pp::Rect &rect, SDL_Color color) :
    _texture(std::move(texture)), _rect(rect), _color(color) {}

void ClickableEntity::onClick(std::function<void()>&& handler) {
    _handler = std::move(handler);
}

void ClickableEntity::click() {
    if (!_handler) return;
    _handler();
}

void ClickableEntity::render(SDL2pp::Renderer *renderer, const int alpha) {
    renderer->SetDrawBlendMode(SDL_BLENDMODE_BLEND);
    auto originalColor = renderer->GetDrawColor();
    int alphaBuffer = _color.a;
    _color.a = alpha;
    renderer->SetDrawColor(_color);
    renderer->FillRect(_rect);
    renderer->SetDrawColor(originalColor);
    renderer->SetDrawBlendMode(SDL_BLENDMODE_NONE);
    renderer->Copy(_texture, SDL2pp::NullOpt, _rect);
    _color.a = alphaBuffer;
}

bool ClickableEntity::contains(int x, int y) {
    return _rect.Contains(x,y);
}

void ClickableEntity::updateTexture(SDL2pp::Texture &&texture) {
    _rect.SetW(texture.GetWidth());
    _texture = std::move(texture);
}
