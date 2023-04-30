#include "inputSys.hpp"


void InputSystem::update(EntityManager& EM, bool& turn){
    EM.forallMatching([&](Entity& e){
        auto& input = EM.getCMPStorage().getInputCMP(e);
        auto& pos = EM.getCMPStorage().getPositionCMP(e);
        keyPressed(input, pos, turn);
    }, cmpMaskToCheck, tagMaskToCheck);
}

void InputSystem::keyPressed(InputCMP& input, PositionCMP& pos, bool& turn){
    
    if ((IsKeyDown(input.KeyW) && pos.posY > 0) ){
        pos.velY -= 1;
        turn = false;
    }else if ((IsKeyDown(input.KeyA) && pos.posX > 0) ){
        pos.velX -= 1;
        turn = false;
    }else if ((IsKeyDown(input.KeyS) && pos.posY < 14) ){
        pos.velY += 1;
        turn = false;
    }else if ((IsKeyDown(input.KeyD) && pos.posX < 14) ){
        pos.velX += 1;
        turn = false;
    } 
}

