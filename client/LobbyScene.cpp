//
// Created by ale on 5/12/21.
//

#include "LobbyScene.h"
LobbyScene::LobbyScene(int numberOfRooms) {
    _numberOfRooms = numberOfRooms;
}

void LobbyScene::updateLoop() {
    clickedInOneRoom = false;
    while(!clickedInOneRoom) {
        this->handleEvents();
        Uint32 deltaTime = Timer::partial();
        //wait if not enough time has passed for it to render another frame
        if (deltaTime < TIME_BETWEEN_FRAMES)
            SDL_Delay(TIME_BETWEEN_FRAMES - deltaTime);
        this->render();
        //time since previous render is 0 again
        Timer::reset();
    }
}

void LobbyScene::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            clickedInOneRoom = clickedInsideOneRoom();
            break;
        }
    }
}

void LobbyScene::render() {
    //clear screen
    _renderer->Clear();

    _renderer->Copy((*backgroundImageTexture), SDL2pp::NullOpt, SDL2pp::Rect(0, 0, _width, _height));
    int roomsFitHorizontally = _width / (messageWidth + xOffset);
    numberOfColumns = roomsFitHorizontally;
    int roomsFitVertically = _height / (messageHeight + yOffset);
    unsigned long int currentRoomNumber = 0;
    for(int i = 0; i < roomsFitVertically && currentRoomNumber < textures.size(); ++i) {
        for(int j = 0; j < roomsFitHorizontally && currentRoomNumber < textures.size(); ++j) {
            SDL2pp::Rect messageRect(
                    j * (messageWidth + xOffset),
                    i * (messageHeight + yOffset),
                    textures[currentRoomNumber]->GetWidth(),
                    textures[currentRoomNumber]->GetHeight()
            );
            _renderer->Copy((*textures[currentRoomNumber]), SDL2pp::NullOpt, messageRect);
            ++currentRoomNumber;
        }
    }
    /*std::cout << "textures: " << textures.size() <<
                " textures rendered: " << currentRoomNumber <<
                " fitHor: " << roomsFitHorizontally <<
                " fitVer: " << roomsFitVertically << std::endl;*/
    //show rendered frame
    _renderer->Present();
}

void LobbyScene::load(SDL2pp::Renderer *renderer) {
    Scene::load(renderer);
    backgroundImageTexture = std::make_unique<SDL2pp::Texture>((*_renderer), LOBBY_BACKGROUND_FILEPATH);
    loadRoomsTextures();
    this->render();
}

void LobbyScene::loadRoomsTextures() {// Initialize SDL_ttf library
    SDL2pp::SDLTTF ttf;
    // Load font
    SDL2pp::Font font("../assets/fonts/Vera.ttf", ROOM_NAME_FONT_SIZE);
    //todo: max text size would be with room 99, look into this
    TTF_SizeText(font.Get(), "Room 99", &messageWidth, &messageHeight);
    for (int i = 0; i < _numberOfRooms; ++i) {
        // add the text into new texture. Note that SDL_ttf render
        // text into Surface, which is converted into texture on the fly
        //std::cout << "." << (*firstMessage) << "." << std::endl;
        textures.push_back(std::make_unique<SDL2pp::Texture>(
                (*_renderer),
                font.RenderText_Blended("Room " + std::to_string(i),SDL_Color{
                        255,
                        255,
                        255,
                        255})));
    }
}

bool LobbyScene::clickedInsideOneRoom() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    float validPercentageX = (float)messageWidth / (float)(messageWidth + xOffset);
    float validPercentageY = (float)messageHeight / (float)(messageHeight + yOffset);
    float clampedMouseXToGrid = (float)mouseX / (float)(messageWidth + xOffset);
    float clampedMouseYToGrid = (float)mouseY / (float)(messageHeight + yOffset);
    int xBoxGridClickPosition = floor(clampedMouseXToGrid);
    int yBoxGridClickPosition = floor(clampedMouseYToGrid);
    //clicked outside of a room box
    if (clampedMouseXToGrid - xBoxGridClickPosition > validPercentageX)
        xBoxGridClickPosition = -1;
    //clicked outside of a room box
    if (clampedMouseYToGrid - yBoxGridClickPosition > validPercentageY)
        yBoxGridClickPosition = -1;
    std::cout << "clicked in " << xBoxGridClickPosition << " and " << yBoxGridClickPosition << std::endl;
    return  xBoxGridClickPosition != -1 &&
            yBoxGridClickPosition != -1 &&
            (yBoxGridClickPosition * numberOfColumns + xBoxGridClickPosition) < _numberOfRooms;
}
