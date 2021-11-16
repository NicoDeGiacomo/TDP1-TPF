#ifndef _GAME_LOBBY_H_
#define _GAME_LOBBY_H_

#include <SDL2pp/SDL2pp.hh>
#include "Screen.h"
#include "Button.h"
#include <vector>

class GameLobby: public Screen {
public:
    GameLobby(SDL2pp::Renderer &renderer, std::string user_name);
    virtual int start() override;
private:
    std::string user_name;
    std::vector<Button> buttons;
    virtual void redraw() override;
    void mousePress(SDL_MouseButtonEvent& b);
};

#endif  // _GAME_LOBBY_H_
