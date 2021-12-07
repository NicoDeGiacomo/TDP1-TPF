//
// Created by ale on 6/12/21.
//

#ifndef QUANTUM_CHESS_TIMER_H
#define QUANTUM_CHESS_TIMER_H


#include <SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

class Timer {
private:
    static void start();
    Timer() = default;
public:
    inline static Uint32 startTime = 0;
    static Uint32 partial() ;
    static Uint32 reset();
};


#endif //QUANTUM_CHESS_TIMER_H
