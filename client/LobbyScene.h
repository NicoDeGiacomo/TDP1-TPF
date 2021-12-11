//
// Created by ale on 5/12/21.
//

#ifndef QUANTUM_CHESS_LOBBYSCENE_H
#define QUANTUM_CHESS_LOBBYSCENE_H


#include <vector>
#include "Scene.h"
#include "Button.h"
#include "ButtonTEMP.h"

#define CONFIG_BUTTON_PNG "../assets/sprites/configButton.png"
#define CONFIG_BUTTON_SIZE_MULTIPLIER .1f
#define LOBBY_BACKGROUND_FILEPATH "../assets/sprites/lobbyBackground.png"
#define X_OFFSET_BETWEEN_ROOMS 20
#define Y_OFFSET_BETWEEN_ROOMS 20
#define FONT_SIZE_MULTIPLIER .045f

class LobbyScene : public Scene {
private:
    int fontSize;
    bool clickedInOneRoom;
    Scene* _configScene;
    std::unique_ptr<SDL2pp::Texture> backgroundImageTexture;
    std::unique_ptr<ButtonTEMP> configButton;
    std::vector<ButtonTEMP> buttons;
    std::unique_ptr<ButtonTEMP> inputTextContainer;
    std::string inputId;
    bool done;

    void loadRoomsTextures();
    void render() override;
    void handleEvents() override;
    void createConfigButton(SDL2pp::Texture &&texture, const SDL2pp::Rect &rect);
    void addButton(std::function<void()>&& onClickHandler, SDL2pp::Texture &&texture, const SDL2pp::Rect &rect, SDL_Color color = {255,255,255, 255});
public:
    explicit LobbyScene(Scene* configScene);
    void updateLoop() override;
    void load(SDL2pp::Renderer* renderer, SDL2pp::Window *window) override;

    //bool clickedInsideOneRoom();
    void handleMouseClick();

    void loadRoomsButtons(SDL2pp::Font& font);

    void loadConfigButton();

    void loadInputRoomId(SDL2pp::Font &font);

    void updateInputText();

    void loadJoinButtons(SDL2pp::Font &font);
};


#endif //QUANTUM_CHESS_LOBBYSCENE_H
