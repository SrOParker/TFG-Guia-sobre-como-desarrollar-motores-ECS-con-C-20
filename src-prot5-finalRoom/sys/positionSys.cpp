#include "positionSys.hpp"

void PositionSystem::update(EntityManager& EM){
    EM.forallMatching([&](Entity& e){
        auto& posCMP = EM.getCMPStorage().getPositionCMP(e); 
        posCMP.posX += posCMP.velX;
        posCMP.posY += posCMP.velY;
        posCMP.velX = posCMP.velY = 0;

    }, cmpMaskToCheck, tagMaskToCheck);
}