#include "positionSys.hpp"

void PositionSystem::update(EntityManager& EM, GameManager& GM){
    EM.forallMatching([&](Entity& e){
        auto& map = GM.getActualMap();
        auto& posCMP = EM.getCMPStorage().getPositionCMP(e); 
        GM.getActualMap()[posCMP.posY][posCMP.posX] = 0;
        if(e.hasTag(Tags::player)){
            int directionX=0;
            if(posCMP.velX<0){ directionX= -1; }else{ directionX = 1; }
            int directionY=0;
            if(posCMP.velY<0){ directionY= -1; }else{ directionY = 1; }
            
            if(posCMP.velX!=0){
                for (int i=0; i<abs(posCMP.velX); i++){
                    if(map[posCMP.posY][posCMP.posX+directionX]==0 && posCMP.posX+directionX >=0 && posCMP.posX+directionX<15){
                        posCMP.posX += directionX;
                    }else{
                        break;
                    }
                }
            }else if(posCMP.velY!=0){
                for (int i=0; i<abs(posCMP.velY); i++){
                    if(map[posCMP.posY+directionY][posCMP.posX]==0 && posCMP.posY+directionY >=0 && posCMP.posY+directionY<15){
                        posCMP.posY += directionY;
                    }else{
                        break;
                    }
                }
            }
        }else{
            posCMP.posX += posCMP.velX;
            posCMP.posY += posCMP.velY;
        }
        posCMP.velX = posCMP.velY = 0;

        //Matriz del mapa actualizada
        if(e.hasTag(Tags::enemy)){
            GM.getActualMap()[posCMP.posY][posCMP.posX] = 3;
        }
    }, cmpMaskToCheck, tagMaskToCheck);
}