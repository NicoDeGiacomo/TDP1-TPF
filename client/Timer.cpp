//
// Created by ale on 6/12/21.
//

#include "Timer.h"

namespace Timer {
    void start(){
        startTime = SDL_GetTicks();
    }

    Uint32 partial(){
        return SDL_GetTicks() - startTime;
    }

    Uint32 reset(){
        Uint32 partial = Timer::partial();
        start();
        return partial;
    }
}