#include "game.hpp"
#include <array>
void Game::run(){
    Map map{};
    SetTargetFPS(60);
    while (!WindowShouldClose()){
        switch (state) {
            case States::MENU:
                reset(0);
                BeginDrawing();
                ClearBackground(RAYWHITE);
                rendSys.renderMenu(map);
                inpSys.menuKeys(States::MENU, state);
                EndDrawing(); 
                break;
            case States::GAME:
                reset(1);
                GM.selectLvlAndGenerate(EM , GM.getActualLvl());
                playing_lvl = true;
                startNormalGame(map);
                break;
            case States::WIKI:

                break;
            case States::ENDGAME:

                break;
        }
    }
}
void Game::reset(int config){
    //std::cout <<"------- ANTES DE BORRAR --------\n";
    //std::cout << "RENDER SLOT: " << EM.getCMPStorage().renderStorage.size()<<"\n";
    //std::cout << "STATS  SLOT: " << EM.getCMPStorage().statsStorage.size()<<"\n";
    //std::cout << "POSITI SLOT: " << EM.getCMPStorage().positionStorage.size()<<"\n";
    //std::cout << "INPUT  SLOT: " << EM.getCMPStorage().inputStorage.size()<<"\n";
    //std::cout << "ENTITIES   : " << EM.getEntityVector().size()<<"\n";
    GM.killPlayer();
    GM.saveInventory(EM);
    EM.removeAllEntities();
    EM.getCMPStorage().clearAllStorage();
    if (config == 0){
        GM.resetLvl();
        playing_lvl = false;
        state = MENU;
    }
    //std::cout <<"------- DESPUES DE BORRAR --------\n";
    //std::cout << "RENDER SLOT: " << EM.getCMPStorage().renderStorage.size()<<"\n";
    //std::cout << "STATS  SLOT: " << EM.getCMPStorage().statsStorage.size()<<"\n";
    //std::cout << "POSITI SLOT: " << EM.getCMPStorage().positionStorage.size()<<"\n";
    //std::cout << "INPUT  SLOT: " << EM.getCMPStorage().inputStorage.size()<<"\n";
    //std::cout << "ENTITIES   : " << EM.getEntityVector().size()<<"\n";
}

void Game::startNormalGame(Map& map){
    while (playing_lvl){
        turn_seconds += GetFrameTime();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (turn){
            inpSys.update(EM, turn, playing_lvl, state);
            turn_seconds = 0;
            
        }else{
            if (turn_seconds >= time){
                iaSys.update(EM, GM);
                turn=true;
                turn_seconds = 0;
            }
        }
        collSys.update(EM, GM, playing_lvl, state);
        posSys.update(EM, GM);
        rendSys.update(EM,GM, map);
        EndDrawing();
    }
}
