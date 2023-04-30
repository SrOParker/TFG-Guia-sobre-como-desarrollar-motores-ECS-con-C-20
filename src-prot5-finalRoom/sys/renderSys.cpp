#include "renderSys.hpp"
void RenderSystem::update(EntityManager& EM, Map& map){
    renderMap(map);
    renderStatsInterface(EM, map);
    EM.forallMatching([&](Entity&e){
        auto& render    = EM.getCMPStorage().getRenderCMP(e); 
        auto& pos       = EM.getCMPStorage().getPositionCMP(e);
        float pos_X = HORIZONTAL_BORDER + pos.posX * SPRITE_DIMENSIONS;
        float pos_Y = VERTICAL_BORDER + pos.posY * SPRITE_DIMENSIONS;
        DrawTextureRec(render.sprite, render.frame, (Vector2){pos_X, pos_Y},WHITE);
    }, cmpMaskToCheck, tagMaskToCheck);
}

void RenderSystem::renderMap(Map& map){

    DrawTexture(map.map,
    (float)(0),
    (float)(0),
    WHITE);

}

void RenderSystem::renderStatsInterface(EntityManager& EM, Map& map){
    auto& statsPLayer = EM.getCMPStorage().getStatsCMP(EM.getPlayer());

    DrawTexture(map.interface.health, (float)(SPRITE_DIMENSIONS/2), 
                (float)(VERTICAL_BORDER+SPRITE_DIMENSIONS*1), WHITE);
    for (int i=0; i<statsPLayer.health; i++){
        DrawTexture(map.interface.point, (float)(SPRITE_DIMENSIONS+20) + i*10, (float)(VERTICAL_BORDER+SPRITE_DIMENSIONS*1.45), WHITE);
    }
    DrawTexture(map.interface.damage, (float)(SPRITE_DIMENSIONS/2), 
                (float)(VERTICAL_BORDER+(SPRITE_DIMENSIONS*2.5)), WHITE);
    for (int i=0; i<statsPLayer.damage; i++){
        DrawTexture(map.interface.point, (float)(SPRITE_DIMENSIONS+20) + i*10, (float)(VERTICAL_BORDER+SPRITE_DIMENSIONS*2.95), WHITE);
    }
    DrawTexture(map.interface.step, (float)(SPRITE_DIMENSIONS/2), 
                (float)(VERTICAL_BORDER+(SPRITE_DIMENSIONS*4)), WHITE);
    for (int i=0; i<statsPLayer.step; i++){
        DrawTexture(map.interface.point, (float)(SPRITE_DIMENSIONS+20) + i*10, (float)(VERTICAL_BORDER+SPRITE_DIMENSIONS*4.45), WHITE);
    }
    DrawTexture(map.interface.pickaxe, (float)(SPRITE_DIMENSIONS/2), 
                (float)(VERTICAL_BORDER+(SPRITE_DIMENSIONS*5.5)), WHITE);
    for (int i=0; i<statsPLayer.pickaxe; i++){
        DrawTexture(map.interface.point, (float)(SPRITE_DIMENSIONS+20) + i*10, (float)(VERTICAL_BORDER+SPRITE_DIMENSIONS*5.95), WHITE);
    }
    DrawTexture(map.interface.critical, (float)(SPRITE_DIMENSIONS/2), 
                (float)(VERTICAL_BORDER+(SPRITE_DIMENSIONS*7)), WHITE);
    for (int i=0; i<statsPLayer.critical_hit; i+=5){
        DrawTexture(map.interface.point, (float)(SPRITE_DIMENSIONS+20) + i*10, (float)(VERTICAL_BORDER+SPRITE_DIMENSIONS*7.45), WHITE);
    }
}