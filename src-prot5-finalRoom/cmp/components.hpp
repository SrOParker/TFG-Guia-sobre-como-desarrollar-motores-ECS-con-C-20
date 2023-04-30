#pragma once
#include <raylib.h>

struct RenderCMP {
    const char* route {};
    Texture2D sprite { LoadTexture(route) };
    int actual_frame = 0;
    Rectangle  frame = {(float)(actual_frame*32), 0,(float)32, (float)sprite.height};
    static int const mask{0b1};
};

struct PositionCMP {
    int posX{};
    int posY{};
    int velX{};
    int velY{};
    static int const mask{0b10};
};

struct StatsCMP {
    int health{};
    int damage{};
    int step{};
    int critical_hit{};
    int pickaxe{};

    static int const mask{0b100};
};

struct InputCMP {
    int KeyW = KEY_W;
    int KeyA = KEY_A;
    int KeyD = KEY_D;
    int KeyS = KEY_S;
    static int const mask{0b1000};
};

struct Tags{
    static int const player         {0b00000001};
    static int const enemy          {0b00000010};
    static int const wall           {0b00000100};
    static int const movement       {0b00001000};
    static int const collider       {0b00010000};
    static int const collisionable  {0b00100000};
    static int const ghost          {0b01000000};
    static int const soldier        {0b10000000};
};