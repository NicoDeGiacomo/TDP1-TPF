#ifndef _LOGIN_H_
#define _LOGIN_H_

#include <SDL2pp/SDL2pp.hh>
#include "Screen.h"
#include "Scene.h"

class LoginScene: public Scene {
public:
    LoginScene();
    /*LoginScene(SDL2pp::Renderer* renderer);
    int start();*/
    std::string get_user_name();
private:
    std::string user_name;
    void insert_text(std::string &text,
                     int font_size,
                     int pos_x,
                     int pos_y,
                     int flags);
    void updateLoop() override;
    void render() override;
    void load(SDL2pp::Renderer* renderer) override;
};

#endif  // _LOGIN_H_
