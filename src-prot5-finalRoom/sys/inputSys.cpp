#include "inputSys.hpp"


void InputSystem::update(EntityManager& EM, bool& turn, bool& playing_lvl, States& state){
    EM.forallMatching([&](Entity& e){
        keyPressed(EM,e,turn, playing_lvl, state);
    }, cmpMaskToCheck, tagMaskToCheck);
}

void InputSystem::keyPressed(EntityManager& EM,Entity& e, bool& turn, bool& playing_lvl, States& state){
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
    }else if (IsKeyDown(KEY_B)){
        playing_lvl = false;
        state = States::MENU;
    }
}

void InputSystem::menuKeys(int config, States& state){
    //configuration for initial menu
    if( config == 0 ){
        if (IsKeyDown(KEY_SPACE)) {
            state = States::GAME;
        }else if (IsKeyDown(KEY_W)){
            //state = States::WIKI;
            std::cout << "Wiki\n";
        }
    }

}