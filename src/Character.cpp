#include <headers/Character.h>

Character::Character(float x, float y, Texture2D tex)
{
    sprite.texture = tex;
    sprite.destRect.x = x;
    sprite.destRect.y = y;
    sprite.destRect.width = 64;
    sprite.destRect.height = 64;

    speed = 100.0f;
    velocity = {0, 0};
    inputVector = {0, 0};
}

Character::~Character()
{
    UnloadTexture(sprite.texture);
}

void Character::move(Vector2 inputVector, float dt)
{
    velocity.x = inputVector.x * speed * dt;
    velocity.y = inputVector.y * speed * dt;
}


void Character::update(float dt)
{
    applyVelocityX();
    applyVelocityY();
}

void Character::draw()
{
    DrawTexturePro(sprite.texture, {0, 0, 16, 16}, sprite.destRect, {0, 0}, 0, WHITE);
}

Vector2 Character::getInput()
{
    // Reset input vector to avoid accumulating input from multiple frames
    inputVector = {0, 0};

    // Handle input from arrow keys
    if (IsKeyDown(KEY_RIGHT)) {
        inputVector.x = 1;  // Move right
    }
    if (IsKeyDown(KEY_LEFT)) {
        inputVector.x = -1;  // Move left
    }
    if (IsKeyDown(KEY_DOWN)) {
        inputVector.y = 1;  // Move down
    }
    if (IsKeyDown(KEY_UP)) {
        inputVector.y = -1;  // Move up
    }

    return inputVector;  // Return the input vector
}

void Character::applyVelocityX() {
    sprite.destRect.x += velocity.x;
}

void Character::applyVelocityY() {
    sprite.destRect.y += velocity.y;
}
