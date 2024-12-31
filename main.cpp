#include <raylib.h>

#include <headers/Character.h>

#define WIDTH 1280
#define HEIGHT 720

int main()
{
    // init app
    InitWindow(WIDTH, HEIGHT, "Retro RPG");
    SetTargetFPS(60);
    float dt = 0.f;
    
    Texture2D playertexture = LoadTexture("assets/characters/protag-sheet.png");
    Character player(0, 0, playertexture);

    // run app
    while (!WindowShouldClose())
    {
        dt = GetFrameTime();
        /* code */

        player.move(player.getInput(), dt);

        player.update(dt);


        // draw
        BeginDrawing();
        
        ClearBackground(BLACK);
        player.draw();
        
        EndDrawing();
    }


    // close app
    CloseWindow();

    /* code */
    return 0;
}
