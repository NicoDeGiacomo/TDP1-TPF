#ifndef _LOGIN_H_
#define _LOGIN_H_

#include <SDL2pp/SDL2pp.hh>
#include "Screen.h"
#include "Scene.h"
#include "ButtonTEMP.h"
#define CONFIG_BUTTON_PNG "../assets/sprites/configButton.png"
#define CONFIG_BUTTON_SIZE_MULTIPLIER .1f

class LoginScene: public Scene {
private:
    std::string &user_name;
    bool done;
    std::unique_ptr<ButtonTEMP> configButton;
    Scene* _configScene;
    void insert_text(std::string &text,
                     int font_size,
                     int pos_x,
                     int pos_y,
                     int flags);
    void render() override;
    void handleEvents() override;
    void addButton(std::function<void()>&& onClickHandler, SDL2pp::Texture &&texture, const SDL2pp::Rect &rect);
public:
    LoginScene(Scene* configScene, std::string &user_name);
    /*LoginScene(SDL2pp::Renderer* renderer);
    int start();*/
    void updateLoop() override;
    void load(SDL2pp::Renderer* renderer, SDL2pp::Window *window) override;

    void loadConfigButton();

    void handleMouseClick();
};

#endif  // _LOGIN_H_
