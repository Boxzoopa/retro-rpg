#pragma once
#include <headers/Scene.h>

class GameScene : public IScene {
public:
    // Constructor and destructor
    //GameScene();
    //~GameScene();

    // init objs
    Texture2D tex;

    // Override the required methods from IScene
    void load() override {
        tex = LoadTexture("assets/items/bait1.png");
    }    // Load the scene


    void update(float dt) override {

    }  // Update the scene


    void draw() override {
        ClearBackground(BLACK);

        // Ensure the destination rectangle is within the screen bounds
        Rectangle destRect = { 100, 100, 64, 64 };  // Adjust coordinates to place the texture visibly on screen
        DrawRectangle(0,0, 100, 100, RED);
        DrawTexturePro(tex, {0, 0, 16, 16}, destRect, {0, 0}, 0, WHITE);
    } // Draw the scene
};
