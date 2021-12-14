#include "ConfigScene.h"
#include "ScreenResolutions.h"
#include <StageMode.h>

void ConfigScene::render() {
    // Clear screen
    _renderer->Clear();
    for (auto& button : buttons)
        button.render(_renderer, 255);
    // Show rendered frame
    _renderer->Present();
}

void ConfigScene::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            handleMouseClick();
            break;
        }
    }
}

void ConfigScene::updateLoop() {
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

void ConfigScene::load(SDL2pp::Renderer *renderer, SDL2pp::Window *window) {
    Scene::load(renderer, window);
    loadResizeButtons();
}

void ConfigScene::loadFullScreenButton(SDL2pp::Font& font, const int yPosition) {
    SDL2pp::Texture texture(
            (*_renderer),
            font.RenderText_Blended("FullScreen",
                                    SDL_Color{22,22,22,255}));
    SDL2pp::Rect buttonRect(
            0,
            yPosition,
            texture.GetWidth(),
            texture.GetHeight()
    );
    addButton([&window = _window]{
        StageMode::log("You clicked fullscreen");
        window->SetFullscreen(SDL_WINDOW_FULLSCREEN_DESKTOP);
    },std::move(texture), buttonRect);
}

void ConfigScene::addButton(std::function<void()>&& onClickHandler, SDL2pp::Texture &&texture, const SDL2pp::Rect &rect) {
    ClickableEntity button(std::move(texture), rect);
    button.onClick(std::move(onClickHandler));
    buttons.push_back(std::move(button));
}

void ConfigScene::handleMouseClick() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    for (auto& button : buttons){
        if (button.contains(mouseX, mouseY)) {
            button.click();
            done = true;
        }
    }
}

void ConfigScene::loadResizeButtons() {
    buttons.clear();
    SDL2pp::SDLTTF ttf;
    // Load font
    int fontSize = _window->GetHeight() * FONT_SIZE_MULTIPLIER;
    SDL2pp::Font font(StageMode::getFullPath("assets/fonts/Vera.ttf"), fontSize);
    int i = 0;
    int yButtonPosition = _window->GetHeight() / (ScreenResolutions::resolutionsCount + 1); // +1 for fullscreen
    loadFullScreenButton(font, i++);
    loadResizeButton(ScreenResolutions::nHD, font, yButtonPosition * i++);
    loadResizeButton(ScreenResolutions::SVGA, font, yButtonPosition * i++);
    loadResizeButton(ScreenResolutions::WXGA, font, yButtonPosition * i++);
    loadResizeButton(ScreenResolutions::SXGA, font, yButtonPosition * i++);
    loadResizeButton(ScreenResolutions::WXGA_PLUS, font, yButtonPosition * i++);
    loadResizeButton(ScreenResolutions::FHD, font, yButtonPosition * i++);
}

void ConfigScene::loadResizeButton(const ScreenResolutions::Resolution &resolution, SDL2pp::Font& font, const int yPosition) {
    SDL2pp::Texture texture(
            (*_renderer),
            font.RenderText_Blended(std::to_string(resolution.width) + "x" + std::to_string(resolution.height),
                                    SDL_Color{22,22,22,255}));
    SDL2pp::Rect buttonRect(
            0,
            yPosition,
            texture.GetWidth(),
            texture.GetHeight()
    );
    addButton([&window = _window,&resolution = resolution]{
        StageMode::log("You clicked resize button");
        window->SetFullscreen(false);
        window->SetSize(resolution.width, resolution.height);
    },std::move(texture), buttonRect);
}
