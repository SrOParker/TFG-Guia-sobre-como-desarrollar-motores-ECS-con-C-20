#include "collisionSys.hpp"


void CollisionSystem::update(EntityManager& EM){
    EM.forallMatching([&](Entity& e){
        auto& posCMPOfCollider = EM.getCMPStorage().getPositionCMP(e);
        if(posCMPOfCollider.velX!=0 || posCMPOfCollider.velY!=0){
            EM.forallMatching([&](Entity& coll){
                auto& posCMPOfCollisionable = EM.getCMPStorage().getPositionCMP(coll);
                if(coll.hasTag(Tags::wall)){
                    collisionWithWall(EM, e, coll, posCMPOfCollider, posCMPOfCollisionable);
                }

            }, cmpMaskToCheck, Tags::collisionable);
        }
    },cmpMaskToCheck, tagMaskToCheck);
}

void CollisionSystem::collisionWithWall(EntityManager& EM, Entity& ent, Entity& wall, PositionCMP& collider, PositionCMP& collisionable){
    //Check Collision
    bool removedHorizontal = false;
    bool removedVertical = false;
    if((collider.velX != 0) && 
        (collisionable.posY == collider.posY && 
        ((collider.posX + collider.velX) == collisionable.posX))){
        //Try moving HORIZONTAL (Key A OR D)
        removedHorizontal = true;
        collider.velX = 0;
               
    }
    
    if((collider.velY != 0) && 
        (collisionable.posX == collider.posX && 
        ((collider.posY + collider.velY) == collisionable.posY))){
        //Try moving VERTICAL (Key W OR S)
        removedVertical = true;
        collider.velY = 0;
    }

    if(removedHorizontal || removedVertical){
        if(ent.hasTag(Tags::player)){    // Hit Wall
            auto& statsPlayer = EM.getCMPStorage().getStatsCMP(ent);
            auto& statsWall = EM.getCMPStorage().getStatsCMP(wall);
            auto& rendWall = EM.getCMPStorage().getRenderCMP(wall);
            statsWall.health -= statsPlayer.pickaxe;
            rendWall.actual_frame++;
            rendWall.frame = {(float)(rendWall.actual_frame*32), 0,(float)32, (float)rendWall.sprite.height};
            if(statsWall.health <= 0){
                //Eliminar Entidad
                EM.removeEntity(wall);
            }
        }
    }
}

