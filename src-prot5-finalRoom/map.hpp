//MAP
#pragma once
#include <raylib.h>

struct Map{
    Texture2D map;
    Rectangle size_map;
    Map(){
        map = LoadTexture("sprites/background.png");
        size_map = {0,0, (float)map.width, (float)map.height};
    }
    ~Map(){
        UnloadTexture(map);
    }
};