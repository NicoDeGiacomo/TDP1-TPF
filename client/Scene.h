//
// Created by ale on 4/12/21.
//

#ifndef QUANTUM_CHESS_SCENE_H
#define QUANTUM_CHESS_SCENE_H
#include <SDL_image.h>
#include <SDL2pp/SDL2pp.hh>
#include "Timer.h"
#define MAIN_BACKGROUND_FILEPATH "assets/sprites/mainBackground.png"

#define TIME_BETWEEN_FRAMES 1000 / 60
#define FONT_SIZE_MULTIPLIER .045f
#define CONFIG_BUTTON_SIZE_MULTIPLIER .1f

class Scene {
protected:
    SDL2pp::Renderer *_renderer;
    SDL2pp::Window *_window;
    SDL2pp::Mixer *_mixer;
    std::vector<std::unique_ptr<SDL2pp::Chunk>> *_sound;
    virtual void render() = 0;
    virtual void handleEvents() = 0;
public:
    virtual void updateLoop() = 0;
    virtual void load(SDL2pp::Renderer *renderer, SDL2pp::Window* window);
    virtual ~Scene() = default;
    void addMixer(SDL2pp::Mixer* mixer, std::vector<std::unique_ptr<SDL2pp::Chunk>> *chunk);
};


#endif //QUANTUM_CHESS_SCENE_H
