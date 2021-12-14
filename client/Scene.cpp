#include "Scene.h"

void Scene::load(SDL2pp::Renderer *renderer, SDL2pp::Window *window) {
    _renderer = renderer;
    _window = window;
}

void Scene::addMixer(SDL2pp::Mixer* mixer, std::vector<std::unique_ptr<SDL2pp::Chunk>> *chunk){
    _mixer = mixer;
    _sound = chunk;
}