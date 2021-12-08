//
// Created by ale on 7/12/21.
//

#include "ButtonTEMP.h"

ButtonTEMP::ButtonTEMP(SDL2pp::Texture &&texture, const SDL2pp::Rect &rect) :
    _texture(std::move(texture)), _rect(rect) {}

void ButtonTEMP::onClick(std::function<void()>&& handler) {
    _handler = std::move(handler);
}

void ButtonTEMP::click() {
    _handler();
}

void ButtonTEMP::render(SDL2pp::Renderer *renderer, const int alpha) {
    renderer->SetDrawBlendMode(SDL_BLENDMODE_BLEND);
    auto originalColor = renderer->GetDrawColor();
    renderer->SetDrawColor(195,195,195,alpha);
    renderer->FillRect(_rect);
    renderer->SetDrawColor(originalColor);
    renderer->SetDrawBlendMode(SDL_BLENDMODE_NONE);
    renderer->Copy(_texture, SDL2pp::NullOpt, _rect);
}

bool ButtonTEMP::contains(int x, int y) {
    return _rect.Contains(x,y);
}
