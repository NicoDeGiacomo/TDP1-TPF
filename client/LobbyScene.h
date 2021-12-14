//
// Created by ale on 5/12/21.
//

#ifndef QUANTUM_CHESS_LOBBYSCENE_H
#define QUANTUM_CHESS_LOBBYSCENE_H


#include <vector>
#include "Scene.h"
#include "ClickableEntity.h"
#include "Entity.h"

#define CONFIG_BUTTON_PNG "../assets/sprites/configButton.png"
#define LOBBY_BACKGROUND_FILEPATH "../assets/sprites/lobbyBackground.png"

class LobbyScene : public Scene {
private:
    int fontSize;
    bool clickedInOneRoom;
    Scene* _configScene;
    std::unique_ptr<SDL2pp::Texture> backgroundImageTexture;
    std::unique_ptr<ClickableEntity> configButton;
    std::vector<ClickableEntity> buttons;
    std::vector<Entity> entities;
    std::unique_ptr<ClickableEntity> inputTextContainer;
    std::string* _roomId;
    char* _playerType;
    bool done;

    void loadRoomsTextures();
    void render() override;
    void handleEvents() override;
    void createConfigButton(SDL2pp::Texture &&texture, const SDL2pp::Rect &rect);
    void addButton(std::function<void()>&& onClickHandler, SDL2pp::Texture &&texture, const SDL2pp::Rect &rect, SDL_Color color = {255,255,255, 255});
public:
    explicit LobbyScene(Scene* configScene, char* playerType, std::string* roomId);
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
