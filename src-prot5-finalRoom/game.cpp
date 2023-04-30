#include "game.hpp"
#include <array>
void Game::run(){
    Map map{};
    createEntities();
    SetTargetFPS(60);
    while (!WindowShouldClose()){
        turn_seconds += GetFrameTime();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (turn){
            inpSys.update(EM, turn);
            turn_seconds = 0;
            
        }else{
            if (turn_seconds >= time){
                iaSys.update(EM, GM);
                turn=true;
                turn_seconds = 0;
            }
        }
        collSys.update(EM);
        posSys.update(EM);
        rendSys.update(EM, map);
        EndDrawing();
    }
}

void Game::createEntities(){

    //GM.selectLvlAndGenerate(EM,GM.Lvl1);
    GM.selectLvlAndGenerate(EM, GM.Lvl1);
}