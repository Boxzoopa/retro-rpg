#pragma once
#include <raylib.h>

// Define the IScene interface as a pure virtual class
class IScene {
public:
    virtual ~IScene() = default;  // Virtual destructor for cleanup in derived classes
    
    // Pure virtual methods that derived classes must implement
    virtual void load() = 0;  // Initialization logic
    virtual void update(float dt) = 0;  // Update game logic each frame
    virtual void draw() = 0;  // Draw the scene to the screen
    //virtual void unload() = 0;  // Clean up when the scene is unloaded
};

