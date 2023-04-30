//MAP
#pragma once
#include <raylib.h>

struct Interface{
    Texture2D health;
    Texture2D damage;
    Texture2D pickaxe;
    Texture2D step;
    Texture2D critical;
    Texture2D point;
};

struct Map{
    Texture2D map;
    Rectangle size_map;
    Interface interface;
    Map(){
        map = LoadTexture("sprites/background_interface.png");
        size_map = {0,0, (float)map.width, (float)map.height};

        interface.health    = LoadTexture("sprites/vida.png");
        interface.damage    = LoadTexture("sprites/ataque.png");
        interface.pickaxe   = LoadTexture("sprites/pico.png");
        interface.step      = LoadTexture("sprites/velocidad.png");
        interface.critical  = LoadTexture("sprites/critico.png");
        interface.point     = LoadTexture("sprites/Punto.png");
    }
    ~Map(){
        UnloadTexture(map);
        UnloadTexture(interface.health);
        UnloadTexture(interface.damage);
        UnloadTexture(interface.pickaxe);
        UnloadTexture(interface.step);
        UnloadTexture(interface.critical);
        UnloadTexture(interface.point);
    }
};