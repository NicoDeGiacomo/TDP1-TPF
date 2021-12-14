#include "SceneManager.h"
#include "ScreenResolutions.h"
#include "StageMode.h"
#include <SDL.h>
#include <SDL_mixer.h>

#include <SDL2pp/SDL.hh>
#include <SDL2pp/Mixer.hh>
#include <SDL2pp/Chunk.hh>

void SceneManager::addScene(std::unique_ptr<Scene> scene, const std::string &sceneName) {
    _scenes[sceneName] = std::move(scene);
}

void SceneManager::loadScene(const std::string& name){
    if (!_scenes.count(name)) return;
    if (!_renderer) loadWindow();
    activeScene = name;
    _scenes[activeScene]->addMixer(_mixer.get(), &_sound);
    _scenes[activeScene]->load(_renderer.get(), _window.get());
}

void SceneManager::updateLoopActiveScene(){
    _scenes[activeScene]->updateLoop();
}

void SceneManager::loadWindow() {
    SDL2pp::SDL(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    _window = std::make_unique<SDL2pp::Window>("Quantum Chess",
                                               SDL_WINDOWPOS_UNDEFINED,
                                               SDL_WINDOWPOS_UNDEFINED,
                                               ScreenResolutions::nHD.width,
                                               ScreenResolutions::nHD.height,
                                               SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    _renderer = std::make_unique<SDL2pp::Renderer>((*_window), -1, SDL_RENDERER_ACCELERATED);
    _mixer = std::make_unique<SDL2pp::Mixer>(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
    std::unique_ptr<SDL2pp::Chunk> sfx = std::make_unique<SDL2pp::Chunk>(StageMode::getFullPath("assets/sounds/chess-move-normal.wav"));
    std::unique_ptr<SDL2pp::Chunk> music = std::make_unique<SDL2pp::Chunk>(StageMode::getFullPath("assets/sounds/music.wav"));
    _sound.push_back(std::move(music));
    _sound.push_back(std::move(sfx));
}
