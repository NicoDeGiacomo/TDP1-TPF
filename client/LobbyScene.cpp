//
// Created by ale on 5/12/21.
//

#include "LobbyScene.h"
#include "Protocol.h"
#include <StageMode.h>

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
                    updateInputText();
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
    for(auto& entity : entities){
        entity.render(_renderer, 255);
    }
    configButton->render(_renderer, 0);
    inputTextContainer->render(_renderer, 255);
    //show rendered frame
    _renderer->Present();
}

void LobbyScene::load(SDL2pp::Renderer *renderer, SDL2pp::Window *window) {
    Scene::load(renderer, window);
    backgroundImageTexture = std::make_unique<SDL2pp::Texture>((*_renderer), MAIN_BACKGROUND_FILEPATH);
    loadRoomsTextures();
    this->render();
}

void LobbyScene::loadRoomsTextures() {
    // Initialize SDL_ttf library
    SDL2pp::SDLTTF ttf;
    // Load font
    fontSize = _window->GetHeight() * FONT_SIZE_MULTIPLIER;
    SDL2pp::Font font("../assets/fonts/Vera.ttf", fontSize);
    loadConfigButton();
    loadInputRoomId(font);
    loadJoinButtons(font);
}

void LobbyScene::createConfigButton(SDL2pp::Texture &&texture, const SDL2pp::Rect &rect) {
    configButton = std::make_unique<ClickableEntity>(std::move(texture), rect);
    configButton->onClick([&configScene = _configScene,
                                  &renderer = _renderer,
                                  &window = _window]{
        StageMode::log("You clicked config");
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
            font.RenderText_Blended("Type room id: ",SDL_Color{255,255,255,255}));
    (*_roomId) = "...";
    SDL2pp::Texture inputRoomIdTexture(
            (*_renderer),
            font.RenderText_Blended((*_roomId),SDL_Color{255,255,255,255}));
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
    entities.emplace_back(std::move(typeRoomIdTexture), typeRoomIdRect);
    inputTextContainer = std::make_unique<Entity>(std::move(inputRoomIdTexture), inputRoomIdRect);
}

void LobbyScene::updateInputText() {
    //so it doesnt crash
    if (_roomId->empty()) return;
    // Initialize SDL_ttf library
    SDL2pp::SDLTTF ttf;
    // Load font
    fontSize = _window->GetHeight() * FONT_SIZE_MULTIPLIER;
    SDL2pp::Font font("../assets/fonts/Vera.ttf", fontSize);
    SDL2pp::Texture texture(
            (*_renderer),
            font.RenderText_Blended((*_roomId),SDL_Color{255,255,255,255}));
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
        StageMode::log("joined room id: ." + (*inputId) + ". as black, char: ." + (*playerType) + ".");
        done = true;
    }, std::move(blackButtonTexture), blackButtonRect, SDL_Color{255,215,0,255});
    addButton([inputId = _roomId, playerType = _playerType, &done = done] {
        (*playerType) = SPECTATOR_CHAR;
        StageMode::log("joined room id: ." + (*inputId) + ". as spectator, char: ." + (*playerType) + ".");
        done = true;
        }, std::move(spectatorButtonTexture), spectatorButtonRect, SDL_Color{255,215,0,255});
    addButton([inputId = _roomId, playerType = _playerType, &done = done] {
        (*playerType) = WHITE_CHAR;
        StageMode::log("joined room id: ." + (*inputId) + ". as white, char: ." + (*playerType) + ".");
        done = true;
    }, std::move(whiteButtonTexture), whiteButtonRect, SDL_Color{255,215,0,255});
}
