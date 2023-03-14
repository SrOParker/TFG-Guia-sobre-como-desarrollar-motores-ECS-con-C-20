#include "game.hpp"


void Game::createEntitiesForFirefighterGameRL(){
    auto& player = EM.createEntity();
    //player.render.sprite= LoadTexture("img/bombero.png");
    player.has_render = true;
    player.has_movement = true;

    for(int i=0; i < 6; i++){
        auto& room_ENTITY = EM.createEntity();
        room_ENTITY.room.fire= rand()%3;
        room_ENTITY.room.position = i;
        room_ENTITY.render.sprite= LoadTexture("img/fire.png");
        room_ENTITY.has_room = true;
        room_ENTITY.has_render = true;
        room_ENTITY.has_movement= false;
    }
}

bool Game::checkRooms(bool& ending){
    for(int i =0 ; i<(int)EM.getEntityVector().size()-1;i++){
        if(EM.getEntityVector()[i+1].room.fire > 9){
            ending = true;   
            return true; 
        }
    }
    return false;
}

void Game::run(){
    //map.setMapBackground("img/menu.png");
    Map map{};
    SetTargetFPS(60);
    createEntitiesForFirefighterGameRL();
    bool running = true;
    bool end = false;
    int score = 0;
    while (!WindowShouldClose()){
        if(!running){break;}
        checkRooms(end);
    
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        if(!end){
            mov_sys.update(EM, running, score);
        }
        rend_sys.update(EM,map, score);
        if(end){
            rend_sys.printLose();
        }
    
        EndDrawing();         
    }
}

