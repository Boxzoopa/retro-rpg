#include <raylib.h>
#include <Map.h>
#include <headers/Character.h>
#include <headers/Menu.h>

#define WIDTH 1280
#define HEIGHT 720

// Dummy character stats for the game menu
struct CharacterStats {
    int level = 5;
    int hp = 120;
    int mp = 80;
    int exp = 1500;
    int cash = 200;
};

int main()
{
    // Initialize the window and set target FPS
    InitWindow(WIDTH, HEIGHT, "Retro RPG");
    SetTargetFPS(60);
    float dt = 0.f;

    // Load player texture and create player object
    Texture2D playerTexture = LoadTexture("assets/characters/protag-sheet.png");
    Character player(0, 0, playerTexture);

    // Initialize the map and load it from file
    Map map("assets/tilesets/overoworld_tileset.png", 16, 16, 0, 0);  // Tile dimensions and spacing
    if (!map.LoadFromFile("assets/maps/testMap.json", 30, 30)) {
        TraceLog(LOG_ERROR, "Failed to load map");
        CloseWindow();
        return -1;
    }

    // Flags to manage menu and game state
    bool gameActive = true;
    bool isMainMenuActive = false;
    bool isGameMenuActive = false;

    // Create main menu with options
    Menu mainMenu({WIDTH / 2 - 150, HEIGHT / 2 - 150}, 40);
    mainMenu.addOption("New");
    mainMenu.addOption("Continue");
    mainMenu.addOption("Options");
    mainMenu.addOption("Quit");

    // Create game menu with options
    Menu gameMenu({10, 10}, 30, 200, 250);
    gameMenu.setOptions({"Party", "Info", "Bag", "Save", "Exit"});

    // Dummy character stats for the game menu
    CharacterStats playerStats;

    // Initialize camera
    Camera2D cam = {0};
    cam.target = {player.sprite.destRect.x + player.sprite.destRect.width / 2, 
                  player.sprite.destRect.y + player.sprite.destRect.height / 2};  // Center on player
    cam.offset = {WIDTH / 2.0f, HEIGHT / 2.0f}; // Camera offset to center on screen
    cam.zoom = 1.0f;  // Set zoom level

    // Main game loop
    while (!WindowShouldClose())
    {
        dt = GetFrameTime();  // Get frame time
        cam.target = {player.sprite.destRect.x + player.sprite.destRect.width / 2, 
                      player.sprite.destRect.y + player.sprite.destRect.height / 2};  // Follow player

        if (gameActive) {
            player.move(player.getInput(), dt);
            player.update(dt);
        }

        // Handle main menu interactions
        if (isMainMenuActive) {
            mainMenu.handleInput();

            if (IsKeyPressed(KEY_ENTER)) {
                if (mainMenu.getSelectedOption() == "Start Game") {
                    isMainMenuActive = false;
                    isGameMenuActive = true;
                } else if (mainMenu.getSelectedOption() == "Exit") {
                    CloseWindow();
                    return 0;
                }
            }
        } 
        // Handle in-game menu interactions
        else if (isGameMenuActive) {
            gameActive = false;
            gameMenu.handleInput();

            if (IsKeyPressed(KEY_X) && !gameActive) {
                std::string selected = gameMenu.getSelectedOption();
                if (selected == "Party") {
                    // Show party members
                } else if (selected == "Info") {
                    // Show player info (e.g., level, HP, MP)
                } else if (selected == "Items") {
                    // Show inventory items
                } else if (selected == "Cash") {
                    // Show cash amount
                } else if (selected == "Exit") {
                    isGameMenuActive = false;
                    gameActive = true;
                }
            }
        }

        // Activate game menu if Enter is pressed while the game is active
        if (IsKeyPressed(KEY_ENTER) && gameActive) {
            isGameMenuActive = true;
        }

        // Draw everything
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(cam);

        map.draw(4);  // Draw the map
        player.draw();  // Draw the player character

        EndMode2D();

        // Draw active menu
        if (isMainMenuActive) {
            mainMenu.draw();
        } else if (isGameMenuActive) {
            gameMenu.draw();  // Draw the game menu

            // Draw character stats at the bottom of the screen
            DrawText(("LVL: " + std::to_string(playerStats.level)).c_str(), 20, HEIGHT - 140, 20, WHITE);
            DrawText(("HP: " + std::to_string(playerStats.hp)).c_str(), 20, HEIGHT - 120, 20, WHITE);
            DrawText(("MP: " + std::to_string(playerStats.mp)).c_str(), 20, HEIGHT - 100, 20, WHITE);
            DrawText(("EXP: " + std::to_string(playerStats.exp)).c_str(), 20, HEIGHT - 80, 20, WHITE);
            DrawText(("Cash: " + std::to_string(playerStats.cash)).c_str(), 20, HEIGHT - 60, 20, WHITE);
        }

        EndDrawing();
    }

    // Close the window
    CloseWindow();
    return 0;
}
