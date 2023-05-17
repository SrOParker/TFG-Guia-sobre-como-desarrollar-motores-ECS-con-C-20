#pragma once
#include <raylib.h>
struct RenderCMP {
    const char* route {};
    Texture2D sprite { LoadTexture(route) };
    int actual_frame = 0;
    Rectangle  frame = {static_cast<float>(actual_frame*32), 0,static_cast<float>(32), static_cast<float>(sprite.height)};
    static const int mask{0b1};
};

struct PositionCMP {
    int posX{};
    int posY{};
    int velX{};
    int velY{};
    static const int mask{0b10};
};

struct StatsCMP {
    int health{};
    int maxhealth{};
    int damage{};
    int step{};
    int critical_hit{};
    int pickaxe{};

    void addStats(StatsCMP obj){
        health += obj.health;
        maxhealth += obj.maxhealth;
        damage += obj.damage;
        step += obj.step;
        critical_hit += obj.critical_hit;
        pickaxe += obj.pickaxe; 
    }
    static const int mask{0b100};
};

struct InputCMP {
    int KeyW = KEY_W;
    int KeyA = KEY_A;
    int KeyD = KEY_D;
    int KeyS = KEY_S;
    static const int mask{0b1000};
};

struct ObjectCMP{
    int obj;
    static const int mask {0b10000};
};

struct DescriptionCMP{
    const char* description{""};
    static const int mask {0b100000};
};

struct Tags{
    static const int player         {0b00000000000001};
    static const int enemy          {0b00000000000010};
    static const int wall           {0b00000000000100};
    static const int movement       {0b00000000001000};
    static const int collider       {0b00000000010000};
    static const int collisionable  {0b00000000100000};
    static const int ghost          {0b00000001000000};
    static const int soldier        {0b00000010000000};
    static const int chest          {0b00000100000000};
    static const int object         {0b00001000000000};
    static const int object_picked  {0b00010000000000};    
    static const int key            {0b00100000000000};
    static const int door           {0b01000000000000};
    static const int has_key        {0b10000000000000};
};

enum Objects{
    Health,
    Damage,
    Steps,
    Critical,
    Pickaxe
};