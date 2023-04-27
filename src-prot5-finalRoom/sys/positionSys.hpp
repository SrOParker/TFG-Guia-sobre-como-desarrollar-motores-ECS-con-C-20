#pragma once
#include <iostream>
#include "../man/manentity.hpp"
#include <raylib.h>


struct PositionSystem{

    void update(EntityManager& EM);
    private:

    int cmpMaskToCheck = PositionCMP::mask; // | StatsCMP::mask; (we can add more with OR operation)
    int tagMaskToCheck = Tags::movement;
};