#pragma once
#include <iostream>
#include "../man/manentity.hpp"
#include "../gameManager.hpp"
#include <raylib.h>
#include "../map.hpp"

struct CollisionSystem{

    void update(EntityManager& EM);
    private:
    void collisionWithWall(EntityManager& EM, Entity& player, Entity& wall, PositionCMP& collider, PositionCMP& collisionable);

    int cmpMaskToCheck = PositionCMP::mask; // | StatsCMP::mask; (we can add more with OR operation)
    int tagMaskToCheck = Tags::collider;
};