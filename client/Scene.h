//
// Created by ale on 4/12/21.
//

#ifndef QUANTUM_CHESS_SCENE_H
#define QUANTUM_CHESS_SCENE_H
#include <SDL_image.h>
#include <SDL2pp/SDL2pp.hh>
#include "Timer.h"

#define TIME_BETWEEN_FRAMES 1000 / 60
#define GENERAL_FONT_SIZE 22

class Scene {
protected:
    SDL2pp::Renderer *_renderer;
    SDL2pp::Window *_window;
    virtual void render() = 0;
    virtual void handleEvents() = 0;
public:
    virtual void updateLoop() = 0;
    virtual void load(SDL2pp::Renderer *renderer, SDL2pp::Window* window);
    virtual ~Scene() = default;
};


#endif //QUANTUM_CHESS_SCENE_H
