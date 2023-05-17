#pragma once
#include <raylib.h>


struct Background{
    Texture2D sprite = LoadTexture("img/background.png");
    Rectangle box    = {0,0, static_cast<float>(sprite.width), static_cast<float>(sprite.height)};
};
struct Wall1{
    Texture2D sprite = LoadTexture("img/pared1.png");
    Rectangle box    = {0,0, static_cast<float>(sprite.width), static_cast<float>(sprite.height)};
};
struct Wall2{
    Texture2D sprite = LoadTexture("img/pared2.png");
    Rectangle box    = {0,0, static_cast<float>(sprite.width), static_cast<float>(sprite.height)};
};
struct NoFire{
    Texture2D sprite = LoadTexture("img/edificio-dentro.png");
    Rectangle box    = {0,0, static_cast<float>(sprite.width), static_cast<float>(sprite.height)};
};
struct Rope{
    Texture2D sprite = LoadTexture("img/cuerda.png");
    Rectangle box    = {0,0, static_cast<float>(sprite.width), static_cast<float>(sprite.height)};
};

struct Map{
    Background background{};
    Wall1 wall1{};
    Wall2 wall2{};
    NoFire nofire{};
    Rope rope{};

    ~Map(){
        UnloadTexture(background.sprite);
        UnloadTexture(wall2.sprite);
        UnloadTexture(wall1.sprite);
        UnloadTexture(nofire.sprite);
        UnloadTexture(rope.sprite);
    }
};