#pragma once
#include <iostream>
#include "../man/manentity.hpp"
#include "../gameManager.hpp"
#include <raylib.h>
#include "../map.hpp"
#include "../states.hpp"

struct CollisionSystem{

    void update(EntityManager& EM, GameManager& GM, bool& playing_lvl, States& state, int& lvlActual);
    private:
    bool checkCollision(PositionCMP& pos1, PositionCMP& pos2);
    void collisionWithWall(EntityManager& EM, GameManager& GM, Entity& player, Entity& wall, PositionCMP& collider);
    void collisionWithEnemy(EntityManager& EM, GameManager& GM, Entity& player, Entity& enemy);
    void collisionWithPlayer(EntityManager& EM, Entity& player, Entity& enemy, States& state, bool& playing_lvl);
    void collisionWithChest(EntityManager& EM, GameManager& GM, Entity& player,  Entity& chest);
    void collisionWithKey(EntityManager& EM, GameManager& GM, Entity& player, Entity& key);
    void collisionWithDoor(bool& playing_lvl, int& lvlActual);
    
    int cmpMaskToCheck = PositionCMP::mask; // | StatsCMP::mask; (we can add more with OR operation)
    int tagMaskToCheck = Tags::collider;
};