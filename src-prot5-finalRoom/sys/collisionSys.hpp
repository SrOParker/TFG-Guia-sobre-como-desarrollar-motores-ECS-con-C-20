#pragma once
#include <iostream>
#include "../man/manentity.hpp"
#include "../gameManager.hpp"
#include <raylib.h>
#include "../map.hpp"

struct CollisionSystem{

    void update(EntityManager& EM, GameManager& GM);
    private:
    bool checkCollision(PositionCMP& pos1, PositionCMP& pos2);
    void collisionWithWall(EntityManager& EM, GameManager& GM, Entity& player, Entity& wall, PositionCMP& collider);
    void collisionWithEnemy(EntityManager& EM, Entity& player, Entity& enemy);
    void collisionWithPlayer(EntityManager& EM, Entity& player, Entity& enemy);
    void collisionWithChest(EntityManager& EM, GameManager& GM, Entity& player,  Entity& chest);

    int cmpMaskToCheck = PositionCMP::mask; // | StatsCMP::mask; (we can add more with OR operation)
    int tagMaskToCheck = Tags::collider;
};