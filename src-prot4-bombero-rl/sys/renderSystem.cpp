#include "renderSystem.hpp"

RenderSystem::RenderSystem(){
    row_size =400 / ROW_NUMBER;
    col_size =700 / COL_NUMBER;
}

void RenderSystem::update(EntityManager& EM, int score){
    
    //std::cout<<"SCORE: "<< score << "\n";
    auto& player = EM.getEntityVector()[0];
    struct Background{
        Texture2D sprite = LoadTexture("img/background.png");
        Rectangle box    = {0,0, (float)sprite.width, (float)sprite.height};
    };
    struct Wall1{
        Texture2D sprite = LoadTexture("img/pared1.png");
        Rectangle box    = {0,0, (float)sprite.width, (float)sprite.height};
    };
    struct Wall2{
        Texture2D sprite = LoadTexture("img/pared2.png");
        Rectangle box    = {0,0, (float)sprite.width, (float)sprite.height};
    };
    struct NoFire{
        Texture2D sprite = LoadTexture("img/edificio-dentro.png");
        Rectangle box    = {0,0, (float)sprite.width, (float)sprite.height};
    };
    struct Rope{
        Texture2D sprite = LoadTexture("img/cuerda.png");
        Rectangle box    = {0,0, (float)sprite.width, (float)sprite.height};
    };
    Background background{};
    Wall1 wall1{};
    Wall2 wall2{};
    NoFire nofire{};
    Rope rope{};
    //draw background
    DrawTextureRec(background.sprite,background.box,(Vector2){0,0}, WHITE);

    //draw player
    for(int i=0; i < EM.getEntityVector().size() - 1 ; i++){
        if(player.movement.yPos==i){
            DrawTextureRec(player.render.sprite, player.render.box, (Vector2){0,player.movement.yPos*row_size},WHITE);
        }else if(player.movement.yPos>i){
            DrawTextureRec(rope.sprite, rope.box, (Vector2){0,(i)*row_size},WHITE);
        }
        //draw wall 1
        DrawTextureRec(wall1.sprite,wall1.box,(Vector2){col_size,(i)*row_size}, WHITE);
        for(int j=0; j < EM.getEntityVector()[i+1].room.fire;j++){
            DrawTextureRec(EM.getEntityVector()[i+1].render.sprite, EM.getEntityVector()[i+1].render.box, (Vector2){col_size*(j+2),EM.getEntityVector()[i+1].room.position*row_size},WHITE);
        }
        for(int j=EM.getEntityVector()[i+1].room.fire; j<10;j++){
            DrawTextureRec(nofire.sprite, nofire.box, (Vector2){col_size*(j+2),EM.getEntityVector()[i+1].room.position*row_size},WHITE);
        }
        DrawTextureRec(wall2.sprite,wall2.box,(Vector2){(COL_NUMBER-1)*col_size,(i)*row_size}, WHITE);
    }
    //pintamos controles
    printText(score);
}


void RenderSystem::printText(int& score){
    //draw text
    std::ostringstream stream;
    stream << std::fixed << "CONTROLS: W - UP | S - DOWN | SPACE - CLEAR  ROOM | ESC - CLOSE GAME \n SCORE: "<< score;
    std::string str = stream.str();
    const char* pointsString = str.c_str();
    Color color{112,154,209,255};
    DrawText(pointsString, 100,360, 13, color);
}

void RenderSystem::printLose(){
    //draw text
    std::ostringstream stream;
    stream << std::fixed << "YOU LOSE --- ESC TO EXIT";
    std::string str = stream.str();
    const char* pointsString = str.c_str();
    Color color{100,111,100,255};
    DrawText(pointsString, 150,190, 30, color);
}