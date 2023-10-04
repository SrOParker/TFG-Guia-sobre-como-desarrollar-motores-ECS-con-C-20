//MAP
#pragma once
#include <raylib.h>

struct Menu{
    Texture2D initial_Menu;
    Texture2D endgame;
    Texture2D wiki;
};

struct Interface{
    Texture2D health;
    Texture2D damage;
    Texture2D pickaxe;
    Texture2D step;
    Texture2D critical;
    Texture2D point;
    Texture2D pointVoid;
    Texture2D crit_text;
};

struct Map{
    Texture2D map;
    Rectangle size_map;
    Interface interface;
    Menu      menu;
    Map(){
        map = LoadTexture("sprites/background_interface.png");
        size_map = {0,0, static_cast<float>(map.width), static_cast<float>(map.height)};

        interface.health    = LoadTexture("sprites/vida.png");
        interface.damage    = LoadTexture("sprites/ataque.png");
        interface.pickaxe   = LoadTexture("sprites/pico.png");
        interface.step      = LoadTexture("sprites/velocidad.png");
        interface.critical  = LoadTexture("sprites/critico.png");
        interface.point     = LoadTexture("sprites/Punto.png");
        interface.pointVoid = LoadTexture("sprites/Punto_Vacio.png");
        interface.crit_text = LoadTexture("sprites/crit.png");

        menu.initial_Menu   = LoadTexture("sprites/menu.png");
        menu.endgame        = LoadTexture("sprites/muerte.png");
        menu.wiki           = LoadTexture("sprites/wiki.png");
    }
    ~Map(){
        UnloadTexture(map);
        
        UnloadTexture(interface.health);
        UnloadTexture(interface.damage);
        UnloadTexture(interface.pickaxe);
        UnloadTexture(interface.step);
        UnloadTexture(interface.critical);
        UnloadTexture(interface.point);
        UnloadTexture(interface.pointVoid);
        UnloadTexture(interface.crit_text);

        UnloadTexture(menu.initial_Menu);
        UnloadTexture(menu.endgame);
        UnloadTexture(menu.wiki);
    }
};