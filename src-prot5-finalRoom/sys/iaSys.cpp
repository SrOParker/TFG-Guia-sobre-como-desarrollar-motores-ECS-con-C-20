#include "iaSys.hpp"

void IASystem::update(EntityManager& EM, GameManager& GM){
    EM.forallMatching([&](Entity& e){
        auto& enemy_pos = EM.getCMPStorage().getPositionCMP(e);
        auto& player_pos = EM.getCMPStorage().getPositionCMP(EM.getPlayer());
        if (isPlayerNearby(player_pos, enemy_pos, 3)){
            //PLAYER CERCA
            //PERSEGUIR
            enemyMovement(GM, player_pos, enemy_pos, 0);
        }else{
            //PLAYER LEJOS - PATRON
            enemyMovement(GM, player_pos, enemy_pos, 1);
        }

    }, cmpMaskToCheck, tagMaskToCheck);
}

bool IASystem::isPlayerNearby(PositionCMP& player_pos, PositionCMP& enemy_pos, int distance){
    int deltaX = abs(enemy_pos.posX - player_pos.posX);
    int deltaY = abs(enemy_pos.posY - player_pos.posY);
    return (deltaX <= distance && deltaY <= distance);
}

void IASystem::enemyMovement(GameManager& GM, PositionCMP& player_pos, PositionCMP& enemy_pos, int mode){
    if( mode == 0 ){
        // Persecución del jugador
            if (player_pos.posX > enemy_pos.posX && !tryMoving(enemy_pos.posX, enemy_pos.posY, 1, 0, GM)) {
                enemy_pos.velX = 1;
            }else if (player_pos.posX < enemy_pos.posX && !tryMoving(enemy_pos.posX, enemy_pos.posY, -1, 0, GM)) {
                enemy_pos.velX = -1;
            }
            if (player_pos.posY > enemy_pos.posY && !tryMoving(enemy_pos.posX, enemy_pos.posY, 0, 1, GM)) {
                enemy_pos.velY = 1;
            } else if (player_pos.posY < enemy_pos.posY && !tryMoving(enemy_pos.posX, enemy_pos.posY, 0, -1, GM)) {
                enemy_pos.velY = -1;
            }   
            if (enemy_pos.velX!=0 && enemy_pos.velY!=0){
                if (abs(player_pos.posX - enemy_pos.posX) > abs(player_pos.posY - enemy_pos.posY)) {
                    enemy_pos.velY = 0;
                }else{
                    enemy_pos.velX = 0;
                }
            }
    }else{
        //Patron aleatorio
        int direction = (rand() % 3 == 1) ? -1 : 1;
        if (rand() % 3 == 1){
            if(direction<0 && !tryMoving(enemy_pos.posX, enemy_pos.posY, direction, 0, GM)){
                enemy_pos.velX += 1 * direction;
            }else if(direction>0 && !tryMoving(enemy_pos.posX, enemy_pos.posY, direction, 0, GM)){
                enemy_pos.velX += 1 * direction;
            }
            
        }else{
            if(direction<0 && !tryMoving(enemy_pos.posX, enemy_pos.posY, 0, direction, GM)){
                enemy_pos.velY += 1 * direction;
            }else if(direction>0 && !tryMoving(enemy_pos.posX, enemy_pos.posY, 0, direction, GM)){
                enemy_pos.velY += 1 * direction;
            }
        }
    }
}

bool IASystem::tryMoving(int posX, int posY, int velX, int velY, GameManager& GM) {
    auto& map = GM.getActualMap();
    int nextPosX = posX + velX;
    int nextPosY = posY + velY;
    if (nextPosX < 0 || nextPosX > 14 || nextPosY < 0 || nextPosY > 14) {
        // Next position goes out of bounds
        return true;
    }
    if (map[nextPosX][nextPosY]!=0) {
        // Next position collides with something
        return true;
    }
    return false;
}
