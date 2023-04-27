#include "inputSys.hpp"


void InputSystem::update(EntityManager& EM){
    EM.forallMatching([&](Entity& e){
        auto& input = EM.getCMPStorage().getInputCMP(e);
        auto& pos = EM.getCMPStorage().getPositionCMP(e);
        keyPressed(input, pos);
    }, cmpMaskToCheck, tagMaskToCheck);
}

void InputSystem::keyPressed(InputCMP& input, PositionCMP& pos){
    
    if ((IsKeyDown(input.KeyW) && pos.posY > 0) && (!controlKeys.w_pressed)){
        pos.velY -= 1;
        controlKeys.w_pressed = true;
    }else if ((IsKeyDown(input.KeyA) && pos.posX > 0) && (!controlKeys.a_pressed)){
        pos.velX -= 1;
        controlKeys.a_pressed = true;
    }else if ((IsKeyDown(input.KeyS) && pos.posY < 14) && (!controlKeys.s_pressed)){
        pos.velY += 1;
        controlKeys.s_pressed = true;
    }else if ((IsKeyDown(input.KeyD) && pos.posX < 14) && (!controlKeys.d_pressed)){
        pos.velX += 1;
        controlKeys.d_pressed = true;
    } 
    
    controlKeys.ControlKeys();
}


void Pressed::ControlKeys(){
    if(IsKeyReleased(KEY_W)){
        w_pressed = false;
    }else if(IsKeyReleased(KEY_A)){
        a_pressed = false;
    }else if(IsKeyReleased(KEY_S)){
        s_pressed = false;
    }else if(IsKeyReleased(KEY_D)){
        d_pressed = false;
    }
}

