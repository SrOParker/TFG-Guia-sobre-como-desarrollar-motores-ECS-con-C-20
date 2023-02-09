#include "renderSystem.hpp"
#include <raylib.h>
#include <iomanip>
#include <sstream>
#include <iostream>
RenderSystem::RenderSystem(){
    fontSize = 20;
}

void RenderSystem::update(EntityManager& EM, float score){

    //draw entities
    EM.forall([&](Entity&e){
        if(e.rend.has_value()){
            float posx = e.phy.value().position.first;
            float posy = e.phy.value().position.second;
            DrawTextureRec(e.rend.value().sprite, e.rend.value().box, (Vector2){posx,posy},WHITE);
        }
    });

    //draw text
    printText(score);
}

void RenderSystem::printText(float score){
    //draw text
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(3) << "Puntuación: "<< score << " km";
    std::string str = stream.str();
    const char* pointsString = str.c_str();
    DrawText(pointsString, 250,15,fontSize, BLUE);
}