//
// Created by ale on 8/12/21.
//

#ifndef QUANTUM_CHESS_CONFIGSCENE_H
#define QUANTUM_CHESS_CONFIGSCENE_H


#include "Scene.h"
#include "ClickableEntity.h"
#include "ScreenResolutions.h"

class ConfigScene : public Scene {
private:
    bool done;
    std::vector<ClickableEntity> buttons;
    void render() override;
    void handleEvents() override;

    void handleMouseClick();

    void loadFullScreenButton(SDL2pp::Font& font, const int yPosition);

    void loadResizeButtons();

    void loadResizeButton(const ScreenResolutions::Resolution &resolution, SDL2pp::Font& font, const int yPosition);

    void addButton(std::function<void()>&& onClickHandler, SDL2pp::Texture &&texture, const SDL2pp::Rect &rect);

public:
    void updateLoop() override;
    void load(SDL2pp::Renderer* renderer, SDL2pp::Window *window) override;
};


#endif //QUANTUM_CHESS_CONFIGSCENE_H
