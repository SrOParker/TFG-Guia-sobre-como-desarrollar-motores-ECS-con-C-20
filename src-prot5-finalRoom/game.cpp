#include "game.hpp"

void Game::run(){
    Map map{};
    createEntities();
    SetTargetFPS(60);
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        rendSys.update(EM, map);
        EndDrawing();
    }
}

void Game::createEntities(){
    //CREAMOS EL PERSONAJE
    auto& player = EM.createEntity();
    EM.getCMPStorage().addRenderCMP(RenderCMP{}, player);
    EM.getCMPStorage().addPositionCMP(PositionCMP{}, player);

    //CREAMOS LAS PIEDRAS DEL NIVEL
    for (int i = 0; i < 15;i++){
        for(int j = 0; j < 15; j++){
            int r = rand()%50;
            if (r < 8){
                auto& pedrolo = EM.createEntity();
                EM.getCMPStorage().addRenderCMP(RenderCMP{"sprites/piedra_2.png"}, pedrolo);
                EM.getCMPStorage().addPositionCMP(PositionCMP{i,j}, pedrolo);
            }else if(r>42){
                auto& pedrolo = EM.createEntity();
                EM.getCMPStorage().addRenderCMP(RenderCMP{"sprites/piedra_1.png"}, pedrolo);
                EM.getCMPStorage().addPositionCMP(PositionCMP{i,j}, pedrolo);
            }
        }
    }
    
}