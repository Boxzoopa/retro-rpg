#pragma once
#include <vector>
#include <headers/Scene.h>

class SceneManager
{
private:
    std::vector<IScene*> scenes;

public:
    //SceneManager(/* args */);
    //~SceneManager();

    void AddScene(IScene* scene) {
        scenes.push_back(scene);
    }

    void RemoveScene(IScene* scene) {
        scenes.pop_back();
    }

    void SwitchScene(IScene* scene) {}

    IScene* GetCurrentScene() {return scenes.back(); }
};
