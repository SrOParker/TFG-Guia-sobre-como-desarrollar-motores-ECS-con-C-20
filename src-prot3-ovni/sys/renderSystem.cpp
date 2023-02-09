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
    printScore(score);
}

void RenderSystem::printScore(float score){
    //draw text
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << "Puntuación: "<< score << " m";
    std::string str = stream.str();
    const char* pointsString = str.c_str();
    Color color{112,154,209,255};
    DrawText(pointsString, 450,375,fontSize, color);
}

void RenderSystem::printRecord(float record){
    //draw text
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << record << " m";
    std::string str = stream.str();
    const char* pointsString = str.c_str();
    DrawText(pointsString, 350,92,fontSize, WHITE);
}

void RenderSystem::printDifficultySelected(int dif){
    std::ostringstream stream;
    stream << dif;
    std::string str = stream.str();
    const char* pointsString = str.c_str();
    DrawText(pointsString, 312,326,fontSize/2, WHITE);
}