#include "renderSys.hpp"
void RenderSystem::update(EntityManager& EM, GameManager& GM, Map& map){
    renderMap(map);
    
    if(EM.getEntityVector().size()>0){
        renderRound(GM);
        renderStatsInterface(EM, map);
        renderObjects(EM);
    }
    EM.forallMatching([&](Entity&e){
        auto& render    = EM.getCMPStorage().getRenderCMP(e); 
        auto& pos       = EM.getCMPStorage().getPositionCMP(e);
        float pos_X = HORIZONTAL_BORDER + pos.posX * SPRITE_DIMENSIONS;
        float pos_Y = VERTICAL_BORDER + pos.posY * SPRITE_DIMENSIONS;
        DrawTextureRec(render.sprite, render.frame, (Vector2){pos_X, pos_Y},WHITE);
    }, cmpMaskToCheck, tagMaskToCheck);

    if(GM.critHit!=0){
        renderCritHit(map, GM);
    }
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

void RenderSystem::renderMenu(Map& map){
    DrawTexture(map.menu.initial_Menu,
    (float)(0),
    (float)(0),
    WHITE);
}

void RenderSystem::renderRound(GameManager& GM){
    //draw text
    std::ostringstream stream;
    stream << "Round: "<< GM.getActualLvl()+1;
    std::string str = stream.str();
    const char* text = str.c_str();
    Color color{20,19,30,255};
    Font font = GetFontDefault();
    font.baseSize *= 2.0f; // aumentar el tamaño en un 100%
    DrawTextEx(font, text, Vector2{15.0f, 576.0f}, 50, 1, color);
}

void RenderSystem::renderEndGame(Map& map){
    DrawTexture(map.menu.endgame,
    (float)(0),
    (float)(0),
    WHITE);
}

void RenderSystem::renderCritHit(Map& map, GameManager& GM){
    float pos_X = (HORIZONTAL_BORDER - 16)+ GM.posx_crit * SPRITE_DIMENSIONS;
    float pos_Y = VERTICAL_BORDER + GM.posy_crit * SPRITE_DIMENSIONS;
    DrawTexture(map.interface.crit_text,
    (float)(pos_X),
    (float)(pos_Y),
    WHITE);
    GM.critHit++;
    if (GM.critHit>25){
        GM.critHit=0;
    }
}

void RenderSystem::renderWiki(EntityManager& EM, Map& map){
    float y{1.2f};
    DrawTexture(map.menu.wiki, (float)(0),(float)(0),WHITE);
    EM.forall([&](Entity&e){
        auto& render = EM.getCMPStorage().getRenderCMP(e); 
        float pos_X  = HORIZONTAL_BORDER/3 + SPRITE_DIMENSIONS;
        float pos_Y  = (VERTICAL_BORDER ) + y * SPRITE_DIMENSIONS;
        DrawTextureRec(render.sprite, render.frame, (Vector2){pos_X, pos_Y},WHITE);
        printDescription(EM, e, pos_X, pos_Y);
        y+=1.1f;

    });
}

void RenderSystem::printDescription(EntityManager& EM, Entity& e, float x, float y){
    auto& desc = EM.getCMPStorage().getDescriptionCMP(e).description;
    //draw text
    std::ostringstream stream;
    stream << desc;
    std::string str = stream.str();
    const char* text = str.c_str();
    Color color{20,19,30,255};
    Font font = GetFontDefault();
    font.baseSize *= 0.7f; // aumentar el tamaño en un 100%
    DrawTextEx(font, text, Vector2{x+36, y+10}, 17, 1, color);
}