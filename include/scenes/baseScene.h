#pragma once
#include <headers/Scene.h>

class BaseScene : public IScene {
public:
    // Initilize objects here

    // Override the required methods from IScene
    void load() override {
        
    }    // Load the objects in the scene


    void update(float dt) override {

    }  // Update the objects in the scene


    void draw() override {
        ClearBackground(BLACK);
       
        DrawRectangle(0,0, 100, 100, RED);
    } // Draw the objects in the scene
};
