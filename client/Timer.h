//
// Created by ale on 6/12/21.
//

#ifndef QUANTUM_CHESS_TIMER_H
#define QUANTUM_CHESS_TIMER_H


#include <SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

namespace Timer {
    Uint32 startTime = 0;
    void start();
    Uint32 partial();
    Uint32 reset();
}


#endif //QUANTUM_CHESS_TIMER_H
