#include <raylib.h>
#include <vector>
#include <string>

class Menu {
private:
    std::vector<std::string> options;  // Menu options for the current menu (e.g., party, items)
    int selectedOption;                // Index of selected option
    Vector2 position;                  // Position of the menu
    int fontSize;                      // Font size for menu items
    Color defaultColor;                // Default color for menu text
    Color selectedColor;               // Color for selected menu item
    Rectangle menuBox;                 // Box around the menu options

public:
    // Constructor
    Menu(Vector2 pos, int fontSize = 20, int width = 300, int height = 400) 
        : selectedOption(0), position(pos), fontSize(fontSize), 
          defaultColor(WHITE), selectedColor(RED) {
        menuBox = { position.x, position.y, (float)width, (float)height };
    }

    // Add menu option
    void addOption(const std::string& option) {
        options.push_back(option);
    }

    // Handle input for navigation
    void handleInput() {
        if (IsKeyPressed(KEY_DOWN)) {
            selectedOption = (selectedOption + 1) % options.size();  // Go down
        }
        if (IsKeyPressed(KEY_UP)) {
            selectedOption = (selectedOption - 1 + options.size()) % options.size();  // Go up
        }
    }

    // Draw the menu
    void draw() {
        // Draw the background box for the menu
        DrawRectangleRec(menuBox, BLACK);
        DrawRectangleLinesEx(menuBox, 4, WHITE); // Border around the box

        // Draw the menu options
        for (size_t i = 0; i < options.size(); ++i) {
            Color color = (i == selectedOption) ? selectedColor : defaultColor;
            DrawText(options[i].c_str(), position.x + 20, position.y + 30 + i * (fontSize + 5), fontSize, color);
        }
    }

    // Get the current selected option
    std::string getSelectedOption() {
        return options[selectedOption];
    }

    // Set menu options (can be used for game stats, etc.)
    void setOptions(const std::vector<std::string>& newOptions) {
        options = newOptions;
    }
};
