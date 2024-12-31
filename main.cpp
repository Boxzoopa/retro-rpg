#include <raylib.h>

int main()
{
    // init app
    int screenWidth = 800;
    int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib window");

    // run app
    while (!WindowShouldClose())
    {
        /* code */

        // draw
        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        DrawText("Hello, world!", 10, 10, 20, LIGHTGRAY);
        
        EndDrawing();
    }


    // close app
    CloseWindow();

    /* code */
    return 0;
}
