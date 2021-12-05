//
// Created by ale on 5/12/21.
//

#ifndef QUANTUM_CHESS_LOBBYSCENE_H
#define QUANTUM_CHESS_LOBBYSCENE_H


#include <vector>
#include "Scene.h"

#define LOBBY_BACKGROUND_FILEPATH "../assets/sprites/lobbyBackground.png"
#define ROOM_NAME_FONT_SIZE 22

class LobbyScene : public Scene {
private:
    int _numberOfRooms;
    const int _width = 940;
    const int _height = 480;
    int messageWidth;
    int messageHeight;
    const int xOffset = _width / 20;
    const int yOffset = _height / 20;
    std::unique_ptr<SDL2pp::Texture> backgroundImageTexture;
    std::vector<std::unique_ptr<SDL2pp::Texture>> textures;

    void loadRoomsTextures();
public:
    LobbyScene(int numberOfRooms);
    void updateLoop() override;
    void render() override;
    void load(SDL2pp::Renderer* renderer) override;

    bool clickedInsideOneRoom();
};


#endif //QUANTUM_CHESS_LOBBYSCENE_H
