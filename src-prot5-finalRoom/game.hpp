#pragma once

#include "man/manentity.hpp"
#include "sys/renderSys.hpp"

struct Game{
    
    EntityManager EM{};
    RenderSystem rendSys{};

    void createEntities(){
        auto& player = EM.createEntity();
        EM.getCMPStorage().addRenderCMP(RenderCMP{}, player);
    }
    void run(){
        //while (!WindowShouldClose()){
            //BeginDrawing();
            //ClearBackground(RAYWHITE);
            createEntities();
            rendSys.update(EM);
            //EndDrawing();
        //}
    }

};