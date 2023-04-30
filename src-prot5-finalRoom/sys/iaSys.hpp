#pragma once
#include <iostream>
#include "../man/manentity.hpp"
#include "../gameManager.hpp"
#include <raylib.h>

struct IASystem{

    void update(EntityManager& EM, GameManager& GM);
    private:

    bool isPlayerNearby(PositionCMP& player, PositionCMP& enemy_pos, int distance);
    void enemyMovement(EntityManager& EM, GameManager& GM, PositionCMP& player_pos, PositionCMP& enemy_pos, int mode);
    bool tryMoving(int posX, int posY, int velX, int velY, GameManager& GM); 
    int cmpMaskToCheck = PositionCMP::mask; // | StatsCMP::mask; (we can add more with OR operation)
    int tagMaskToCheck = Tags::movement | Tags::enemy | Tags::collider;
};