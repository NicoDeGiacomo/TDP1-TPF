//
// Created by ale on 7/12/21.
//

#include "ClickableEntity.h"

ClickableEntity::ClickableEntity(SDL2pp::Texture &&texture, const SDL2pp::Rect &rect, SDL_Color color) :
    Entity(std::move(texture), rect, color) {}

void ClickableEntity::onClick(std::function<void()>&& handler) {
    _handler = std::move(handler);
}

void ClickableEntity::click() {
    if (!_handler) return;
    _handler();
}

bool ClickableEntity::contains(int x, int y) {
    return _rect.Contains(x,y);
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
