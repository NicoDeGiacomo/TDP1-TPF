//
// Created by ale on 5/12/21.
//

#include "LobbyScene.h"
#include "Protocol.h"
LobbyScene::LobbyScene(Scene* configScene, char* playerType, std::string* roomId) {
    _playerType = playerType;
    _roomId = roomId;
    _configScene = configScene;
}

void LobbyScene::updateLoop() {
    done = false;
    while(!done) {
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
        switch (event.type) {
            case SDL_KEYDOWN:
                //Handle backspace
                if( event.key.keysym.sym == SDLK_BACKSPACE && _roomId->length() > 0 ) {
                    _roomId->pop_back();
                }
                    //Handle copy
                else if( event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL ) {
                    SDL_SetClipboardText( _roomId->c_str() );
                }
                    //Handle paste
                else if( event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL ) {
                    (*_roomId) += SDL_GetClipboardText();
                    updateInputText();
                }
                break;
            case SDL_QUIT:
                /* Quit */
                done = true;
                break;
            case SDL_TEXTINPUT:
                /* Add new text onto the end of our text */
                (*_roomId) += event.text.text;
                updateInputText();
                break;
            case SDL_MOUSEBUTTONDOWN:
                handleMouseClick();
                break;
        }
    }
}

void LobbyScene::render() {
    //clear screen
    _renderer->Clear();

    _renderer->Copy((*backgroundImageTexture), SDL2pp::NullOpt,
                    SDL2pp::Rect(0, 0, _window->GetWidth(), _window->GetHeight()));
    for(auto& button : buttons){
        button.render(_renderer, 255);
    }
    configButton->render(_renderer, 0);
    inputTextContainer->render(_renderer, 255);
    //show rendered frame
    _renderer->Present();
}

void LobbyScene::load(SDL2pp::Renderer *renderer, SDL2pp::Window *window) {
    Scene::load(renderer, window);
    backgroundImageTexture = std::make_unique<SDL2pp::Texture>((*_renderer), LOBBY_BACKGROUND_FILEPATH);
    loadRoomsTextures();
    this->render();
}

void LobbyScene::loadRoomsTextures() {
    // Initialize SDL_ttf library
    SDL2pp::SDLTTF ttf;
    // Load font
    fontSize = _window->GetHeight() * FONT_SIZE_MULTIPLIER;
    SDL2pp::Font font("../assets/fonts/Vera.ttf", fontSize);
    //loadRoomsButtons(font);
    loadConfigButton();
    loadInputRoomId(font);
    loadJoinButtons(font);
}

void LobbyScene::createConfigButton(SDL2pp::Texture &&texture, const SDL2pp::Rect &rect) {
    configButton = std::make_unique<ClickableEntity>(std::move(texture), rect);
    configButton->onClick([&configScene = _configScene,
                                  &renderer = _renderer,
                                  &window = _window]{
        std::cout << "You clicked config" << std::endl;
        configScene->load(renderer, window);
        configScene->updateLoop();
    });
}

void LobbyScene::handleMouseClick(){
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    if (configButton->contains(mouseX,mouseY)){
        configButton->click();
        //reload scene
        load(_renderer, _window);
        return;
    } else if (inputTextContainer->contains(mouseX,mouseY)){
        _roomId->clear();
        updateInputText();
        return;
    }

    for (auto& button : buttons){
        //ask button if contains mouse position
        if (button.contains(mouseX, mouseY)) {
            button.click();
            return;
        }
    }
}

void LobbyScene::addButton(std::function<void()>&& onClickHandler,
                           SDL2pp::Texture &&texture,
                           const SDL2pp::Rect &rect,
                           SDL_Color color) {
    ClickableEntity button(std::move(texture), rect, color);
    button.onClick(std::move(onClickHandler));
    buttons.push_back(std::move(button));
}

/*void LobbyScene::loadRoomsButtons(SDL2pp::Font& font) {
    buttons.clear();
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
}*/

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

void LobbyScene::loadInputRoomId(SDL2pp::Font &font) {
    buttons.clear();
    SDL2pp::Texture typeRoomIdTexture(
            (*_renderer),
            font.RenderText_Blended("Type Room id: ",SDL_Color{22,22,22,255}));
    (*_roomId) = "click here to clear message...";
    SDL2pp::Texture inputRoomIdTexture(
            (*_renderer),
            font.RenderText_Blended((*_roomId),SDL_Color{22,22,22,255}));
    //1/3 of the screen in y, center of the screen in x
    SDL2pp::Rect typeRoomIdRect(
            _window->GetWidth() / 2 - typeRoomIdTexture.GetWidth(),
            _window->GetHeight() / 3,
            typeRoomIdTexture.GetWidth(),
            typeRoomIdTexture.GetHeight()
    );
    SDL2pp::Rect inputRoomIdRect(
            _window->GetWidth() / 2,
            _window->GetHeight() / 3,
            inputRoomIdTexture.GetWidth(),
            inputRoomIdTexture.GetHeight()
    );
    addButton(nullptr, std::move(typeRoomIdTexture), typeRoomIdRect);
    inputTextContainer = std::make_unique<ClickableEntity>(std::move(inputRoomIdTexture), inputRoomIdRect);
    inputTextContainer->onClick([inputId = _roomId] { (*inputId) = ""; std::cout << "asd" << std::endl; });
}

void LobbyScene::updateInputText() {
    //so it doesnt crash
    if (_roomId->empty())
        (*_roomId) = " ";
    // Initialize SDL_ttf library
    SDL2pp::SDLTTF ttf;
    // Load font
    fontSize = _window->GetHeight() * FONT_SIZE_MULTIPLIER;
    SDL2pp::Font font("../assets/fonts/Vera.ttf", fontSize);
    SDL2pp::Texture texture(
            (*_renderer),
            font.RenderText_Blended((*_roomId),SDL_Color{22,22,22,255}));
    inputTextContainer->updateTexture(std::move(texture));
}

void LobbyScene::loadJoinButtons(SDL2pp::Font &font) {
    SDL2pp::Texture blackButtonTexture(
            (*_renderer),
            font.RenderText_Blended("black",SDL_Color{22,22,22,255}));
    SDL2pp::Rect blackButtonRect(
            _window->GetWidth() / 4 - blackButtonTexture.GetWidth() / 2,
            _window->GetHeight() * 2 / 3,
            blackButtonTexture.GetWidth(),
            blackButtonTexture.GetHeight()
    );
    SDL2pp::Texture spectatorButtonTexture(
            (*_renderer),
            font.RenderText_Blended("spectator",SDL_Color{22,22,22,255}));
    SDL2pp::Rect spectatorButtonRect(
            _window->GetWidth() * 2 / 4 - spectatorButtonTexture.GetWidth() / 2,
            _window->GetHeight() * 2 / 3,
            spectatorButtonTexture.GetWidth(),
            spectatorButtonTexture.GetHeight()
    );
    SDL2pp::Texture whiteButtonTexture(
            (*_renderer),
            font.RenderText_Blended("white",SDL_Color{22,22,22,255}));
    SDL2pp::Rect whiteButtonRect(
            _window->GetWidth() * 3 / 4 - whiteButtonTexture.GetWidth() / 2,
            _window->GetHeight() * 2 / 3,
            whiteButtonTexture.GetWidth(),
            whiteButtonTexture.GetHeight()
    );
    addButton([inputId = _roomId, playerType = _playerType, &done = done] {
        (*playerType) = BLACK_CHAR;
        std::cout << "joined room id: ." + (*inputId) + ". as black, char: ." << (*playerType) << "." << std::endl;
        done = true;
    }, std::move(blackButtonTexture), blackButtonRect, SDL_Color{255,215,0,255});
    addButton([inputId = _roomId, playerType = _playerType, &done = done] {
        (*playerType) = SPECTATOR_CHAR;
        std::cout << "joined room id: ." + (*inputId) + ". as spectator, char: ." << (*playerType) << "." << std::endl;
        done = true;
        }, std::move(spectatorButtonTexture), spectatorButtonRect, SDL_Color{255,215,0,255});
    addButton([inputId = _roomId, playerType = _playerType, &done = done] {
        (*playerType) = WHITE_CHAR;
        std::cout << "joined room id: ." + (*inputId) + ". as white, char: ." << (*playerType) << "." << std::endl;
        done = true;
    }, std::move(whiteButtonTexture), whiteButtonRect, SDL_Color{255,215,0,255});
}
