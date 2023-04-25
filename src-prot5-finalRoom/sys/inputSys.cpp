#include "inputSys.hpp"


void InputSystem::update(EntityManager& EM){
    EM.forallMatching([&](Entity& e){
        auto& input = EM.getCMPStorage().getInputCMP(e);
        auto& pos = EM.getCMPStorage().getPositionCMP(e);
        keyPressed(input, pos);
    }, maskToCheck);
}

void InputSystem::keyPressed(InputCMP& input, PositionCMP& pos){
    
    if (IsKeyDown(input.KeyW) && pos.posY > 0){
        pos.posY -= 1;
    }else if (IsKeyDown(input.KeyA) && pos.posX > 0){
        pos.posX -= 1;
    }else if (IsKeyDown(input.KeyS) && pos.posY < 14){
        pos.posY += 1;
    }else if (IsKeyDown(input.KeyD) && pos.posX < 14){
        pos.posX += 1;
    } 
}

