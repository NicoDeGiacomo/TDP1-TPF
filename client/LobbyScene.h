//
// Created by ale on 5/12/21.
//

#ifndef QUANTUM_CHESS_LOBBYSCENE_H
#define QUANTUM_CHESS_LOBBYSCENE_H


#include <vector>
#include "Scene.h"
#include "Button.h"
#include "ButtonTEMP.h"

#define LOBBY_BACKGROUND_FILEPATH "../assets/sprites/lobbyBackground.png"
#define ROOM_NAME_FONT_SIZE 22

class LobbyScene : public Scene {
private:
    int _numberOfRooms;
    bool clickedInOneRoom;
    const int _width = 780;
    const int _height = 480;
    const int xOffset = _width / 20;
    const int yOffset = _height / 20;
    std::unique_ptr<SDL2pp::Texture> backgroundImageTexture;
    std::vector<ButtonTEMP> buttons;

    void loadRoomsTextures();
    void render() override;
    void handleEvents() override;
public:
    explicit LobbyScene(int numberOfRooms);
    void updateLoop() override;
    void load(SDL2pp::Renderer* renderer) override;

    bool clickedInsideOneRoom();

    void addButton(const int number, SDL2pp::Texture &&texture, const SDL2pp::Rect &rect);
};


#endif //QUANTUM_CHESS_LOBBYSCENE_H
