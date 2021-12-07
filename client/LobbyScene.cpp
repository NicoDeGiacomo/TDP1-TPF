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
    for(auto& button : buttons){
        button.render(_renderer, 255);
    }
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
    int messageWidth, messageHeight;
    //todo: max text size would be with room 99, look into this
    TTF_SizeText(font.Get(), "Room 99", &messageWidth, &messageHeight);

    int roomsFitHorizontally = _width / (messageWidth + xOffset);
    int roomsFitVertically = _height / (messageHeight + yOffset);
    int currentRoomNumber = 0;
    for(int i = 0; i < roomsFitVertically && currentRoomNumber < _numberOfRooms; ++i) {
        for(int j = 0; j < roomsFitHorizontally && currentRoomNumber < _numberOfRooms; ++j) {
            SDL2pp::Texture texture((*_renderer),
                            font.RenderText_Blended(
                                    "Room " + std::to_string(currentRoomNumber),
                                    SDL_Color{22,22,22,255}));
            SDL2pp::Rect buttonRect(
                    j * (messageWidth + xOffset),
                    i * (messageHeight + yOffset),
                    messageWidth,
                    messageHeight
            );
            addButton(currentRoomNumber, std::move(texture), buttonRect);
            ++currentRoomNumber;
        }
    }
    //todo: if (currentRoomNumber < _numberOfRooms) add logic to add rooms beyond the screen size, like scrolling or something
}

bool LobbyScene::clickedInsideOneRoom(){
    for (auto& button : buttons){
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        //ask button if contains mouse position
        if (button.contains(mouseX, mouseY)) {
            button.click();
            return true;
        }
    }
    return false;
}

void LobbyScene::addButton(const int number, SDL2pp::Texture &&texture, const SDL2pp::Rect &rect) {
    std::cout << "added button " + std::to_string(number) << std::endl;
    ButtonTEMP button(std::move(texture), rect);
    button.onClick([number]{ std::cout << "You clicked room number " + std::to_string(number) << std::endl; });
    buttons.push_back(std::move(button));

}
