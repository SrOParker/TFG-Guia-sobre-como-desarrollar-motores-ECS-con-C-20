#pragma once
#include <iostream>
#include "../man/manentity.hpp"
#include <raylib.h>
#include "../map.hpp"

#define HORIZONTAL_BORDER 160
#define HORIZONTAL_MIDDLE 480
#define VERTICAL_BORDER 64
#define VERTICAL_MIDDLE 480
#define SPRITE_DIMENSIONS 32

struct RenderSystem{

    void update(EntityManager& EM, Map& map);
    private:
    void renderMap(Map& map);
    int cmpMaskToCheck = RenderCMP::mask | PositionCMP::mask; // | StatsCMP::mask; (we can add more with OR operation)
    int tagMaskToCheck = 0;
};