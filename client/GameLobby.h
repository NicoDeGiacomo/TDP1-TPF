#ifndef _GAME_LOBBY_H_
#define _GAME_LOBBY_H_

#include <SDL2pp/SDL2pp.hh>
#include "Screen.h"

class GameLobby: public Screen {
public:
    GameLobby(SDL2pp::Renderer &renderer, std::string user_name);
    virtual int start() override;
private:
    std::string user_name;
    virtual void redraw() override;
};

#endif  // _GAME_LOBBY_H_
