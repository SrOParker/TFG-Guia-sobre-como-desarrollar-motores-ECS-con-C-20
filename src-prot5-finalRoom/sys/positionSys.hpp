#pragma once
#include <iostream>
#include "../man/manentity.hpp"
#include <raylib.h>
#include "../gameManager.hpp"

struct PositionSystem{

    void update(EntityManager& EM, GameManager& GM);
    private:

    int cmpMaskToCheck = PositionCMP::mask; // | StatsCMP::mask; (we can add more with OR operation)
    int tagMaskToCheck = Tags::movement;
};