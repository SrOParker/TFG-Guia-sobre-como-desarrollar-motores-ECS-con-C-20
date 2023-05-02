#include "renderSys.hpp"
void RenderSystem::update(EntityManager& EM, Map& map){
    renderMap(map);
    renderStatsInterface(EM, map);
    renderObjects(EM);
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
    
    auto& statsPlayer = EM.getCMPStorage().getStatsCMP(EM.getPlayer());
    DrawTexture(map.interface.health, (float)(SPRITE_DIMENSIONS/2), 
                (float)(VERTICAL_BORDER+SPRITE_DIMENSIONS*1), WHITE);
    for (int i=0;i<statsPlayer.maxhealth; i++){
        if(i < statsPlayer.health){
            DrawTexture(map.interface.point, (float)(SPRITE_DIMENSIONS+20) + i*10, (float)(VERTICAL_BORDER+SPRITE_DIMENSIONS*1.45), WHITE);
        }else{
            DrawTexture(map.interface.pointVoid, (float)(SPRITE_DIMENSIONS+20) + i*10, (float)(VERTICAL_BORDER+SPRITE_DIMENSIONS*1.45), WHITE);
        }
    }
    DrawTexture(map.interface.damage, (float)(SPRITE_DIMENSIONS/2), 
                (float)(VERTICAL_BORDER+(SPRITE_DIMENSIONS*2.5)), WHITE);
    for (int i=0; i<statsPlayer.damage; i++){
        DrawTexture(map.interface.point, (float)(SPRITE_DIMENSIONS+20) + i*10, (float)(VERTICAL_BORDER+SPRITE_DIMENSIONS*2.95), WHITE);
    }
    DrawTexture(map.interface.step, (float)(SPRITE_DIMENSIONS/2), 
                (float)(VERTICAL_BORDER+(SPRITE_DIMENSIONS*4)), WHITE);
    for (int i=0; i<statsPlayer.step; i++){
        DrawTexture(map.interface.point, (float)(SPRITE_DIMENSIONS+20) + i*10, (float)(VERTICAL_BORDER+SPRITE_DIMENSIONS*4.45), WHITE);
    }
    DrawTexture(map.interface.pickaxe, (float)(SPRITE_DIMENSIONS/2), 
                (float)(VERTICAL_BORDER+(SPRITE_DIMENSIONS*5.5)), WHITE);
    for (int i=0; i<statsPlayer.pickaxe; i++){
        DrawTexture(map.interface.point, (float)(SPRITE_DIMENSIONS+20) + i*10, (float)(VERTICAL_BORDER+SPRITE_DIMENSIONS*5.95), WHITE);
    }
    DrawTexture(map.interface.critical, (float)(SPRITE_DIMENSIONS/2), 
                (float)(VERTICAL_BORDER+(SPRITE_DIMENSIONS*7)), WHITE);
    for (int i=0; i<statsPlayer.critical_hit; i+=5){
        DrawTexture(map.interface.point, (float)(SPRITE_DIMENSIONS+20) + (i/5)*10, (float)(VERTICAL_BORDER+SPRITE_DIMENSIONS*7.45), WHITE);
    }
}

void RenderSystem::renderObjects(EntityManager& EM){
    int nextRow = 1;
    int nextCol = 0;
    EM.forallMatching([&](Entity& e){
        if(nextCol == 3){ nextRow++; nextCol=0; } 
        auto& object = e;
        auto& objectRender = EM.getCMPStorage().getRenderCMP(object);
        DrawTexture(objectRender.sprite, 
                (float)((HORIZONTAL_BORDER+HORIZONTAL_MIDDLE + (SPRITE_DIMENSIONS+SPRITE_DIMENSIONS/2 - 3) + (SPRITE_DIMENSIONS*nextCol))), 
                (float)((VERTICAL_BORDER+(SPRITE_DIMENSIONS*nextRow))), 
                WHITE);
        nextCol++;
    }, RenderCMP::mask, Tags::object);

}