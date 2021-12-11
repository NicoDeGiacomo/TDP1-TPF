//
// Created by ale on 7/12/21.
//

#include "ButtonTEMP.h"

ButtonTEMP::ButtonTEMP(SDL2pp::Texture &&texture, const SDL2pp::Rect &rect, SDL_Color color) :
    _texture(std::move(texture)), _rect(rect), _color(color) {}

void ButtonTEMP::onClick(std::function<void()>&& handler) {
    _handler = std::move(handler);
}

void ButtonTEMP::click() {
    if (!_handler) return;
    _handler();
}

void ButtonTEMP::render(SDL2pp::Renderer *renderer, const int alpha) {
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

bool ButtonTEMP::contains(int x, int y) {
    return _rect.Contains(x,y);
}

void ButtonTEMP::updateTexture(SDL2pp::Texture &&texture) {
    _rect.SetW(texture.GetWidth());
    _texture = std::move(texture);
}
