#ifndef _LOGIN_H_
#define _LOGIN_H_

#include <SDL2pp/SDL2pp.hh>
#include "Scene.h"
#include "ClickableEntity.h"
#define CONFIG_BUTTON_PNG "assets/sprites/configButton.png"

class LoginScene: public Scene {
private:
    std::string &userName;
    std::vector<Entity> entities;
    std::unique_ptr<SDL2pp::Texture> backgroundImageTexture;
    std::unique_ptr<Entity> inputTextContainer;
    bool done;
    std::unique_ptr<ClickableEntity> configButton;
    Scene* _configScene;
    void render() override;
    void handleEvents() override;
    void addButton(std::function<void()>&& onClickHandler, SDL2pp::Texture &&texture, const SDL2pp::Rect &rect);
public:
    LoginScene(Scene* configScene, std::string &user_name);
    void updateLoop() override;
    void load(SDL2pp::Renderer* renderer, SDL2pp::Window *window) override;

    void loadConfigButton();

    void handleMouseClick();

    void loadAllTextEntities();

    void updateInputText();
};

#endif  // _LOGIN_H_
