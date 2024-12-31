#include <raylib.h>
#include <cjson/cJSON.h>
#include <string>
#include <fstream>
#include <iostream>

class Map {
private:
    int* mapData;               // Array of tile IDs
    int mapWidth, mapHeight;    // Dimensions of the map in tiles
    int tileWidth, tileHeight;  // Dimensions of each tile
    int margin, spacing;        // Margins and spacing in the tileset
    Texture2D tileset;          // Tileset texture
    int tilesPerRow;            // Number of tiles per row in the tileset

public:
    // Constructor
    Map(const char* tilesetPath, int tileW, int tileH, int m, int s) 
        : mapData(nullptr), mapWidth(0), mapHeight(0),
          tileWidth(tileW), tileHeight(tileH), margin(m), spacing(s) {
        tileset = LoadTexture(tilesetPath);
        tilesPerRow = (tileset.width - 2 * margin + spacing) / (tileWidth + spacing);
    }

    // Destructor
    ~Map() {
        if (mapData) delete[] mapData;
        UnloadTexture(tileset);
    }

    // Load map data from a JSON file
    bool LoadFromFile(const char* filename, int width, int height) {
        mapWidth = width;
        mapHeight = height;

        std::ifstream file(filename);
        if (!file.is_open()) {
            TraceLog(LOG_ERROR, "Failed to open map file: %s", filename);
            return false;
        }

        std::string jsonStr((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        cJSON* json = cJSON_Parse(jsonStr.c_str());
        if (!json) {
            TraceLog(LOG_ERROR, "Failed to parse JSON file: %s", filename);
            return false;
        }

        cJSON* layers = cJSON_GetObjectItem(json, "layers");
        if (!layers) {
            TraceLog(LOG_ERROR, "No layers found in map file: %s", filename);
            cJSON_Delete(json);
            return false;
        }

        cJSON* layer = cJSON_GetArrayItem(layers, 0); // Use the first layer
        cJSON* data = cJSON_GetObjectItem(layer, "data");
        if (!data) {
            TraceLog(LOG_ERROR, "No data found in layer: %s", filename);
            cJSON_Delete(json);
            return false;
        }

        // Allocate memory for map data and read the tile IDs
        mapData = new int[mapWidth * mapHeight];
        for (int i = 0; i < mapWidth * mapHeight; i++) {
            cJSON* tile = cJSON_GetArrayItem(data, i);
            mapData[i] = tile ? tile->valueint : 0; // Default to 0 for empty tiles
        }

        cJSON_Delete(json);
        return true;
    }

    // Draw the map
    void draw(int scale = 1) {
        for (int i = 0; i < mapWidth * mapHeight; i++) {
            int tileId = mapData[i] - 1; // Convert 1-based Tiled IDs to 0-based
            if (tileId < 0) continue;   // Skip empty tiles (ID 0)

            // Calculate the source rectangle in the tileset
            int tileX = margin + (tileId % tilesPerRow) * (tileWidth + spacing);
            int tileY = margin + (tileId / tilesPerRow) * (tileHeight + spacing);

            // Source rectangle in tileset texture
            Rectangle sourceRec = { 
                (float)tileX, 
                (float)tileY, 
                (float)tileWidth, 
                (float)tileHeight 
            };

            // Calculate the destination position on the screen (with scaling)
            int screenX = (i % mapWidth) * tileWidth * scale;
            int screenY = (i / mapWidth) * tileHeight * scale;

            // Destination rectangle on screen (scaled)
            Rectangle destRec = {
                (float)screenX, 
                (float)screenY, 
                (float)(tileWidth * scale), 
                (float)(tileHeight * scale)
            };

            // Draw the tile on the screen
            DrawTexturePro(tileset, sourceRec, destRec, (Vector2){ 0.0f, 0.0f }, 0.0f, WHITE);
        }
    }
};
