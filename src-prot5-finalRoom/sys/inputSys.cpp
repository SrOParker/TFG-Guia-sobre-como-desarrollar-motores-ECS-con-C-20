#include "inputSys.hpp"


void InputSystem::update(EntityManager& EM, bool& turn){
    EM.forallMatching([&](Entity& e){
        keyPressed(EM,e,turn);
    }, cmpMaskToCheck, tagMaskToCheck);
}

void InputSystem::keyPressed(EntityManager& EM,Entity& e, bool& turn){
    auto& input = EM.getCMPStorage().getInputCMP(e);
    auto& pos   = EM.getCMPStorage().getPositionCMP(e);
    auto& stats = EM.getCMPStorage().getStatsCMP(e);
    if ((IsKeyDown(input.KeyW) && pos.posY > 0) ){
        pos.velY = -stats.step;
        turn = false;
    }else if ((IsKeyDown(input.KeyA) && pos.posX > 0) ){
        pos.velX = -stats.step;
        turn = false;
    }else if ((IsKeyDown(input.KeyS) && pos.posY < 14) ){
        pos.velY = stats.step;
        turn = false;
    }else if ((IsKeyDown(input.KeyD) && pos.posX < 14) ){
        pos.velX = stats.step;
        turn = false;
    } 
}

