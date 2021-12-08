//
// Created by ale on 4/12/21.
//

#ifndef QUANTUM_CHESS_SCENEMANAGER_H
#define QUANTUM_CHESS_SCENEMANAGER_H


#include <initializer_list>
#include <string>
#include <unordered_map>
#include <memory>
#include "Scene.h"

class SceneManager {
private:
    std::unique_ptr<SDL2pp::Renderer> _renderer;
    std::unique_ptr<SDL2pp::Window> _window;
    std::unordered_map<std::string,std::unique_ptr<Scene>> _scenes;
    std::string activeScene;

    void loadWindow();
public:
    SceneManager() = default;
    void addScene(std::unique_ptr<Scene> scene, const std::string& sceneName);
    void loadScene(const std::string& name);

    void updateLoopActiveScene();

    //void renderActiveScene();
};


#endif //QUANTUM_CHESS_SCENEMANAGER_H
