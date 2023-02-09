#pragma once
#include <raylib.h>
#include <iostream>

struct Map{
    Map();
    void drawAndMoveMap();
    void textureCleaner(Texture2D& tex);
    Vector2 getMapPositions();
    float getScreenSpeed();
    Texture2D& getMapBackground();
    void setMapPositions(Vector2 positions);
    void setMapSpeed(float sp);
    void setMapBackground(const char* route);
    
    private:
    
    float map_x;
    float map_y;
    float speed;
    Texture2D background;
};