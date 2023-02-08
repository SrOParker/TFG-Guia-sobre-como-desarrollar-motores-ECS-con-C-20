#include "renderSystem.hpp"
#include <raylib.h>
void RenderSystem::update(EntityManager& EM){
    EM.forall([&](Entity&e){
        if(e.rend.has_value()){
            float posx = e.phy.value().position.first;
            float posy = e.phy.value().position.second;
            DrawTextureRec(e.rend.value().sprite, e.rend.value().box, (Vector2){posx,posy},WHITE);
        }
    });
}