#include "LoginScene.h"
#include <StageMode.h>
#include <SDL2pp/SDL2pp.hh>

void LoginScene::updateLoop() {
    done = false;
    while (!done && !_gameFinished) {
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

void LoginScene::handleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE) {
                    _gameFinished = true;
                    StageMode::log("QUIT GAME");
                    return;
                }
                //Handle backspace
                else if( event.key.keysym.sym == SDLK_BACKSPACE && userName.length() > 0 ) {
                    userName.pop_back();
                    updateInputText();
                }
                    //Handle copy
                else if( event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL ) {
                    SDL_SetClipboardText(userName.c_str() );
                }
                    //Handle paste
                else if( event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL ) {
                    userName += SDL_GetClipboardText();
                    updateInputText();
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_RETURN && !userName.empty())
                    done = SDL_TRUE;
                break;
            case SDL_QUIT:
                /* Quit */
                done = SDL_TRUE;
                _gameFinished = true;
                StageMode::log("QUIT GAME");
                return;
            case SDL_TEXTINPUT:
                /* Add new text onto the end of our text */
                userName += event.text.text;
                updateInputText();
                break;
            case SDL_MOUSEBUTTONDOWN:
                handleMouseClick();
                break;
        }
    }
}

void LoginScene::render() {
	// Clear screen
	_renderer->Clear();
    _renderer->Copy((*backgroundImageTexture), SDL2pp::NullOpt,
                    SDL2pp::Rect(0, 0, _window->GetWidth(), _window->GetHeight()));

    for (auto& entity : entities){
        entity.render(_renderer, 255);
    }
    this->inputTextContainer->render(_renderer, 255);
    this->configButton->render(_renderer, 0);
	// Show rendered frame
	_renderer->Present();
}

void LoginScene::load(SDL2pp::Renderer *renderer, SDL2pp::Window *window) {
    Scene::load(renderer, window);
    //load scene, but dont process input nor render textures
    backgroundImageTexture = std::make_unique<SDL2pp::Texture>((*_renderer), StageMode::getFullPath(MAIN_BACKGROUND_FILEPATH));
    this->loadConfigButton();
    this->loadAllTextEntities();
    this->render();
}

LoginScene::LoginScene(Scene* configScene, std::string &user_name, bool& gameFinished) : userName(user_name), _gameFinished(gameFinished) {
    _configScene = configScene;
}

void LoginScene::loadConfigButton() {
    SDL2pp::Texture texture((*_renderer), StageMode::getFullPath(CONFIG_BUTTON_PNG));
    int configButtonSize = _window->GetHeight() * CONFIG_BUTTON_SIZE_MULTIPLIER;
    SDL2pp::Rect buttonRect(
            _window->GetWidth() - configButtonSize,
            0,
            configButtonSize,
            configButtonSize
    );
    addButton([&configScene = _configScene,
                      &renderer = _renderer,
                      &window = _window]{
        StageMode::log("You clicked config");
        configScene->load(renderer, window);
        configScene->updateLoop();
    },std::move(texture), buttonRect);
}

void LoginScene::addButton(std::function<void()>&& onClickHandler, SDL2pp::Texture &&texture, const SDL2pp::Rect &rect) {
    configButton = std::make_unique<ClickableEntity>(std::move(texture), rect);
    configButton->onClick(std::move(onClickHandler));
}

void LoginScene::handleMouseClick() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    if (configButton->contains(mouseX,mouseY)) {
        configButton->click();
        //reload scene
        load(_renderer, _window);
    }
}

void LoginScene::loadAllTextEntities() {
    // Initialize SDL_ttf library
    SDL2pp::SDLTTF ttf;
    // Load font
    int fontSize = _window->GetHeight() * FONT_SIZE_MULTIPLIER;
    SDL2pp::Font font(StageMode::getFullPath("assets/fonts/Vera.ttf"), fontSize);
    entities.clear();
    SDL2pp::Texture titleTexture(
            (*_renderer),
            font.RenderText_Blended("Welcome to Quantum Chess",SDL_Color{255,255,255,255}));
    SDL2pp::Texture chooseUsernameTexture(
            (*_renderer),
            font.RenderText_Blended("Please choose your username:",SDL_Color{255,255,255,255}));
    SDL2pp::Texture inputText(
            (*_renderer),
            font.RenderText_Blended(" ",SDL_Color{255,255,255,255}));
    //1/3 of the screen in y, center of the screen in x
    SDL2pp::Rect titleRect(
            _window->GetWidth() / 2 - (titleTexture.GetWidth() / 2),
            _window->GetHeight() / 3,
            titleTexture.GetWidth(),
            titleTexture.GetHeight()
    );
    SDL2pp::Rect chooseUsernameRect(
            _window->GetWidth() / 2 - (chooseUsernameTexture.GetWidth() / 2),
            _window->GetHeight() / 3 + titleTexture.GetHeight(),
            chooseUsernameTexture.GetWidth(),
            chooseUsernameTexture.GetHeight()
    );
    SDL2pp::Rect inputTextRect(
            _window->GetWidth() / 2 - (chooseUsernameTexture.GetWidth() / 2),
            _window->GetHeight() / 3 + titleTexture.GetHeight() + chooseUsernameTexture.GetHeight(),
            chooseUsernameTexture.GetWidth(),
            chooseUsernameTexture.GetHeight()
    );
    entities.emplace_back(std::move(titleTexture), titleRect);
    entities.emplace_back(std::move(chooseUsernameTexture), chooseUsernameRect);
    inputTextContainer = std::make_unique<Entity>(std::move(inputText), inputTextRect);
}

void LoginScene::updateInputText() {
    //so it doesnt crash
    std::string text = userName;
    if (userName.empty()) text = " ";
    // Initialize SDL_ttf library
    SDL2pp::SDLTTF ttf;
    // Load font
    int fontSize = _window->GetHeight() * FONT_SIZE_MULTIPLIER;
    SDL2pp::Font font(StageMode::getFullPath("assets/fonts/Vera.ttf"), fontSize);
    SDL2pp::Texture texture(
            (*_renderer),
            font.RenderText_Blended(text, SDL_Color{255, 255, 255, 255}));
    inputTextContainer->updateTexture(std::move(texture));
}
