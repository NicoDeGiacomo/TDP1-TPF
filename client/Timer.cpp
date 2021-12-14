#include "Timer.h"

void Timer::start(){
    startTime = SDL_GetTicks();
}

Uint32 Timer::partial() {
    return SDL_GetTicks() - startTime;
}

Uint32 Timer::reset(){
    Uint32 partial = Timer::partial();
    start();
    return partial;
}