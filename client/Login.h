#ifndef LOGIN_H_
#define LOGIN_H_

#include <SDL2pp/SDL2pp.hh>


class Login {
public:
    Login(SDL2pp::Renderer &renderer);
    void start();
private:
    SDL2pp::Renderer &renderer;
    void insert_title(std::string &text);
};

#endif  // LOGIN_H_
