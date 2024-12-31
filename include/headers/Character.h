#include <raylib.h>
#include <cmath>
#include <headers/Sprite.h>

class Character
{
private:
    /* data */
public:
    Sprite sprite;
    Vector2 velocity;
    Vector2 inputVector;
    float speed;

    Character(float x, float y, Texture2D tex);
    ~Character();

    void move(Vector2 inputVector, float dt);
    void update(float dt);
    void draw();

    // update functions
    Vector2 getInput();
    void applyVelocityX();
    void applyVelocityY();
    void checkCollisionX();
    void checkCollisionY();
};

