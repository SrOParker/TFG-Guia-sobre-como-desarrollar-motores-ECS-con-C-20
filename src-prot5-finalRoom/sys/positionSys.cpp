#include "positionSys.hpp"

void PositionSystem::update(EntityManager& EM, GameManager& GM){
    EM.forallMatching([&](Entity& e){
        auto& posCMP = EM.getCMPStorage().getPositionCMP(e); 
        GM.getActualMap()[posCMP.posY][posCMP.posX] = 0;
        posCMP.posX += posCMP.velX;
        posCMP.posY += posCMP.velY;
        posCMP.velX = posCMP.velY = 0;

        //Matriz del mapa actualizada
        if(e.hasTag(Tags::enemy)){
            GM.getActualMap()[posCMP.posX][posCMP.posY] = 3;
        }
    }, cmpMaskToCheck, tagMaskToCheck);
}