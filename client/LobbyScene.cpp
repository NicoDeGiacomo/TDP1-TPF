//
// Created by ale on 5/12/21.
//

#include "LobbyScene.h"
LobbyScene::LobbyScene(int numberOfRooms, Scene* configScene) {
    _numberOfRooms = numberOfRooms;
    _configScene = configScene;
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

    _renderer->Copy((*backgroundImageTexture), SDL2pp::NullOpt,
                    SDL2pp::Rect(0, 0, _window->GetWidth(), _window->GetHeight()));
    for(auto& button : roomButtons){
        button.render(_renderer, 255);
    }
    configButton->render(_renderer, 0);
    //show rendered frame
    _renderer->Present();
}

void LobbyScene::load(SDL2pp::Renderer *renderer, SDL2pp::Window *window) {
    Scene::load(renderer, window);
    backgroundImageTexture = std::make_unique<SDL2pp::Texture>((*_renderer), LOBBY_BACKGROUND_FILEPATH);
    loadRoomsTextures();
    this->render();
}

void LobbyScene::loadRoomsTextures() {// Initialize SDL_ttf library
    SDL2pp::SDLTTF ttf;
    // Load font
    SDL2pp::Font font("../assets/fonts/Vera.ttf", ROOM_NAME_FONT_SIZE);
    loadRoomsButtons(font);
    loadConfigButton();
}

void LobbyScene::createConfigButton(SDL2pp::Texture &&texture, const SDL2pp::Rect &rect) {
    configButton = std::make_unique<ButtonTEMP>(std::move(texture), rect);
    configButton->onClick([&configScene = _configScene,
                                  &renderer = _renderer,
                                  &window = _window]{
        std::cout << "You clicked config" << std::endl;
        configScene->load(renderer, window);
        configScene->updateLoop();
    });
}

bool LobbyScene::clickedInsideOneRoom(){
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    if (configButton->contains(mouseX,mouseY)){
        configButton->click();
        //reload scene
        load(_renderer, _window);
        return false;
    }

    for (auto& button : roomButtons){
        //ask button if contains mouse position
        if (button.contains(mouseX, mouseY)) {
            button.click();
            return true;
        }
    }
    return false;
}

void LobbyScene::addButton(std::function<void()>&& onClickHandler, SDL2pp::Texture &&texture, const SDL2pp::Rect &rect) {
    ButtonTEMP button(std::move(texture), rect);
    button.onClick(std::move(onClickHandler));
    roomButtons.push_back(std::move(button));
}

void LobbyScene::loadRoomsButtons(SDL2pp::Font& font) {
    roomButtons.clear();
    int messageWidth, messageHeight;
    //todo: max text size would be with room 99, look into this
    TTF_SizeText(font.Get(), "Room 99", &messageWidth, &messageHeight);
    int xOffset = _window->GetWidth() / X_OFFSET_BETWEEN_ROOMS;
    int yOffset = _window->GetHeight() / Y_OFFSET_BETWEEN_ROOMS;
    int roomsFitHorizontally = _window->GetWidth() / (messageWidth + xOffset);
    int roomsFitVertically = _window->GetHeight() / (messageHeight + yOffset);
    int currentRoomNumber = 0;
    for(int i = 0; i < roomsFitVertically && currentRoomNumber < _numberOfRooms; ++i) {
        for(int j = 0; j < roomsFitHorizontally && currentRoomNumber < _numberOfRooms; ++j) {
            SDL2pp::Texture texture(
                    (*_renderer),
                    font.RenderText_Blended("Room " + std::to_string(currentRoomNumber),
                                            SDL_Color{22,22,22,255}));
            SDL2pp::Rect buttonRect(
                    j * (messageWidth + xOffset),
                    i * (messageHeight + yOffset),
                    messageWidth,
                    messageHeight
            );
            addButton([currentRoomNumber]{
                    std::cout << "You clicked room number " + std::to_string(currentRoomNumber) << std::endl;
                },std::move(texture), buttonRect);
            ++currentRoomNumber;
        }
    }
    //todo: if (currentRoomNumber < _numberOfRooms) add logic to add rooms beyond the screen size, like scrolling or something
}

void LobbyScene::loadConfigButton() {
    SDL2pp::Texture texture((*_renderer), CONFIG_BUTTON_PNG);
    int configButtonSize = _window->GetHeight() * CONFIG_BUTTON_SIZE_MULTIPLIER;
    SDL2pp::Rect buttonRect(
            _window->GetWidth() - configButtonSize,
            0,
            configButtonSize,
            configButtonSize
    );
    createConfigButton(std::move(texture), buttonRect);
}
