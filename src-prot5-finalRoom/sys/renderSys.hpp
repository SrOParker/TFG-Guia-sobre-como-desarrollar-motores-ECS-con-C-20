#pragma once
#include <iostream>
#include "../man/manentity.hpp"
#include <raylib.h>
#include <sstream>
#include "../map.hpp"
#include "../gameManager.hpp"
#define HORIZONTAL_BORDER 160
#define HORIZONTAL_MIDDLE 480
#define VERTICAL_BORDER 64
#define VERTICAL_MIDDLE 480
#define SPRITE_DIMENSIONS 32

struct RenderSystem{

    void update(EntityManager& EM, GameManager& GM, Map& map);
    void renderMenu(Map& map);
    private:
    void renderMap(Map& map);
    void renderStatsInterface(EntityManager& EM, Map& map);
    void renderObjects(EntityManager& EM);
    void renderRound(GameManager& GM);

    int cmpMaskToCheck = RenderCMP::mask | PositionCMP::mask; // | StatsCMP::mask; (we can add more with OR operation)
    int tagMaskToCheck = 0;
};