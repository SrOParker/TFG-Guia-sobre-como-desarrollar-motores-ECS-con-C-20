#include "collisionSys.hpp"


void CollisionSystem::update(EntityManager& EM, GameManager& GM){
    EM.forallMatching([&](Entity& e){
        auto& posCMPOfCollider = EM.getCMPStorage().getPositionCMP(e);
        if(posCMPOfCollider.velX!=0 || posCMPOfCollider.velY!=0){
            EM.forallMatching([&](Entity& coll){
                auto& posCMPOfCollisionable = EM.getCMPStorage().getPositionCMP(coll);
                if(checkCollision(posCMPOfCollider, posCMPOfCollisionable)){
                    if(coll.hasTag(Tags::wall)){
                        collisionWithWall(EM, GM, e, coll, posCMPOfCollider);
                    }else if(!e.hasTag(Tags::enemy) && coll.hasTag(Tags::enemy)){
                        collisionWithEnemy(EM, e, coll);
                    }else if(e.hasTag(Tags::enemy) && coll.hasTag(Tags::player)){
                        collisionWithPlayer(EM, coll, e);
                    }
                }


            }, cmpMaskToCheck, Tags::collisionable);
        }
    },cmpMaskToCheck, tagMaskToCheck);
}

void CollisionSystem::collisionWithWall(EntityManager& EM, GameManager& GM, Entity& ent, Entity& wall, PositionCMP& collider){
    //Check Collision
    collider.velX = 0;
    collider.velY = 0;

    if(ent.hasTag(Tags::player)){    // Hit Wall
        auto& statsPlayer = EM.getCMPStorage().getStatsCMP(ent);
        auto& statsWall = EM.getCMPStorage().getStatsCMP(wall);
        auto& rendWall = EM.getCMPStorage().getRenderCMP(wall);
        auto& posWall = EM.getCMPStorage().getPositionCMP(wall);
        statsWall.health -= statsPlayer.pickaxe;
        rendWall.actual_frame++;
        rendWall.frame = {(float)(rendWall.actual_frame*32), 0,(float)32, (float)rendWall.sprite.height};
        if(statsWall.health <= 0){
            //Eliminar Entidad
            GM.getActualMap()[posWall.posY][posWall.posX] = 0;
            EM.removeEntity(wall);
        }
    }
    
}

void CollisionSystem::collisionWithEnemy(EntityManager& EM, Entity& player, Entity& enemy){
    auto& player_stats  = EM.getCMPStorage().getStatsCMP(player);
    auto& player_pos    = EM.getCMPStorage().getPositionCMP(player);
    auto& enemy_stats   = EM.getCMPStorage().getStatsCMP(enemy);

    player_pos.velX = 0;
    player_pos.velY = 0;
    if(rand() % 100 <= player_stats.critical_hit){
        enemy_stats.health = enemy_stats.health - player_stats.damage*2;
    }else{
        enemy_stats.health = enemy_stats.health - player_stats.damage;
    }

    if (enemy_stats.health <= 0){
        EM.removeEntity(enemy);
    }

}

bool CollisionSystem::checkCollision(PositionCMP& pos1, PositionCMP& pos2){
    bool removedHorizontal = false;
    bool removedVertical = false;
    if((pos1.velX != 0) && 
        (pos2.posY == pos1.posY && 
        ((pos1.posX + pos1.velX) == pos2.posX))){
        //Try moving HORIZONTAL (Key A OR D)
        removedHorizontal = true;
        pos1.velX = 0;
    }
    
    if((pos1.velY != 0) && 
        (pos2.posX == pos1.posX && 
        ((pos1.posY + pos1.velY) == pos2.posY))){
        //Try moving VERTICAL (Key W OR S)
        removedVertical = true;
        pos1.velY = 0;
    }
    if(removedHorizontal || removedVertical){
        return true;
    }
    return false;
}

void CollisionSystem::collisionWithPlayer(EntityManager& EM, Entity& player, Entity& enemy){
    auto& player_stats  = EM.getCMPStorage().getStatsCMP(player);
    auto& enemy_pos     = EM.getCMPStorage().getPositionCMP(enemy);
    auto& enemy_stats   = EM.getCMPStorage().getStatsCMP(enemy);
    
    player_stats.health -= enemy_stats.damage;
    enemy_pos.velX = 0;
    enemy_pos.velY = 0;

    if(player_stats.health <= 0){
        //Morimos
        std::cout<< "Has muerto\n";
        
    }

}