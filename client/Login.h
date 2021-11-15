#ifndef _LOGIN_H_
#define _LOGIN_H_

#include <SDL2pp/SDL2pp.hh>
#include "Screen.h"

class Login: public Screen {
public:
    Login(SDL2pp::Renderer &renderer);
    virtual int start() override;
    std::string get_user_name();
private:
    std::string user_name;
    virtual void redraw() override;
};

#endif  // _LOGIN_H_
