#include "collisionSys.hpp"


void CollisionSystem::update(EntityManager& EM){
    EM.forallMatching([&](Entity& e){
        auto& posCMPOfCollider = EM.getCMPStorage().getPositionCMP(e);
        if(posCMPOfCollider.velX!=0 || posCMPOfCollider.velY!=0){
            EM.forallMatching([&](Entity& coll){
                auto& posCMPOfCollisionable = EM.getCMPStorage().getPositionCMP(coll);
                if(coll.hasTag(Tags::wall)){
                    collisionWithWall(posCMPOfCollider, posCMPOfCollisionable);
                }

            }, cmpMaskToCheck, Tags::collisionable);
        }
    },cmpMaskToCheck, tagMaskToCheck);
}

void CollisionSystem::collisionWithWall(PositionCMP& collider, PositionCMP& collisionable){
    if((collider.velX != 0) && 
        (collisionable.posY == collider.posY && 
        ((collider.posX + collider.velX) == collisionable.posX))){
        //Try moving HORIZONTAL (Key A OR D)
        collider.velX = 0;
    }else if((collider.velY != 0) && 
        (collisionable.posX == collider.posX && 
        ((collider.posY + collider.velY) == collisionable.posY))){
        //Try moving top (Key W OR S)
        collider.velY = 0;
    }
}