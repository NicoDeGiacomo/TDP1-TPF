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
#define ROOM_NAME_FONT_SIZE 22
#define X_OFFSET_BETWEEN_ROOMS 20
#define Y_OFFSET_BETWEEN_ROOMS 20

class LobbyScene : public Scene {
private:
    int _numberOfRooms;
    bool clickedInOneRoom;
    Scene* _configScene;
    std::unique_ptr<SDL2pp::Texture> backgroundImageTexture;
    std::unique_ptr<ButtonTEMP> configButton;
    std::vector<ButtonTEMP> roomButtons;

    void loadRoomsTextures();
    void render() override;
    void handleEvents() override;
    void createConfigButton(SDL2pp::Texture &&texture, const SDL2pp::Rect &rect);
    void addButton(std::function<void()>&& onClickHandler, SDL2pp::Texture &&texture, const SDL2pp::Rect &rect);
public:
    explicit LobbyScene(int numberOfRooms, Scene* configScene);
    void updateLoop() override;
    void load(SDL2pp::Renderer* renderer, SDL2pp::Window *window) override;

    bool clickedInsideOneRoom();

    void loadRoomsButtons(SDL2pp::Font& font);

    void loadConfigButton();
};


#endif //QUANTUM_CHESS_LOBBYSCENE_H
