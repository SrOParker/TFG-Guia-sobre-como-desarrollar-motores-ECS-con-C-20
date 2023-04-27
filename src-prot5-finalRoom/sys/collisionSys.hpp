#pragma once
#include <iostream>
#include "../man/manentity.hpp"
#include <raylib.h>


struct CollisionSystem{

    void update(EntityManager& EM);
    private:
    void collisionWithWall(PositionCMP& collider, PositionCMP& collisionable);

    int cmpMaskToCheck = PositionCMP::mask; // | StatsCMP::mask; (we can add more with OR operation)
    int tagMaskToCheck = Tags::collider;
};