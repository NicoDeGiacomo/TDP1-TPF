//
// Created by ale on 4/12/21.
//

#include "SceneManager.h"

void SceneManager::addScene(std::unique_ptr<Scene> scene, const std::string &sceneName) {
    _scenes[sceneName] = std::move(scene);
}

void SceneManager::loadScene(const std::string& name){
    if (!_scenes.count(name)) return;
    if (!_renderer) loadWindow();
    activeScene = name;
    _scenes[activeScene]->load(_renderer.get());
}

void SceneManager::updateLoopActiveScene(){
    _scenes[activeScene]->updateLoop();
}

/*void SceneManager::renderActiveScene(){
    _scenes[activeScene]->render();
}*/

void SceneManager::loadWindow() {
    SDL2pp::SDL(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    _window = std::make_unique<SDL2pp::Window>("Quantum Chess",
                                               SDL_WINDOWPOS_UNDEFINED,
                                               SDL_WINDOWPOS_UNDEFINED,
                                               screenWidth,
                                               screenHeight,
                                               SDL_WINDOW_RESIZABLE);
    _renderer = std::make_unique<SDL2pp::Renderer>((*_window), -1, SDL_RENDERER_ACCELERATED);
}
