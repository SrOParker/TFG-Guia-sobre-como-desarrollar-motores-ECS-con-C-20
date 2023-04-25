#include "renderSys.hpp"
void RenderSystem::update(EntityManager& EM, Map& map){
    renderMap(map);
    EM.forallMatching([&](Entity&e){
        auto& render    = EM.getCMPStorage().getRenderCMP(e); 
        auto& pos       = EM.getCMPStorage().getPositionCMP(e);
        float pos_X = HORIZONTAL_BORDER + pos.posX * SPRITE_DIMENSIONS;
        float pos_Y = VERTICAL_BORDER + pos.posY * SPRITE_DIMENSIONS;
        DrawTextureRec(render.sprite, render.frame, (Vector2){pos_X, pos_Y},WHITE);
    }, maskToCheck);
}

void RenderSystem::renderMap(Map& map){

    DrawTexture(map.map,
    (float)(0),
    (float)(0),
    WHITE);

}
