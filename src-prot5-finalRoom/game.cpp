#include "game.hpp"
#include <array>
void Game::run(){
    Map map{};
    createEntities();
    SetTargetFPS(60);
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        inpSys.update(EM);
        rendSys.update(EM, map);
        EndDrawing();
    }
}

void Game::createEntities(){

    //GM.selectLvlAndGenerate(EM,GM.Lvl1);
    GM.selectLvlAndGenerate(EM, GM.Random);
}