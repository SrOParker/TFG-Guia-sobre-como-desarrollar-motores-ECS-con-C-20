#include "collisionSystem.hpp"

void CollisionSystem::update(EntityManager& EM, Texture2D& tex, float& speed){
    auto& player = EM.getEntityVector()[0];
    EM.forall([&](Entity& e){
        if(e.coll.has_value() && e.id != player.id){
            bool collision = CheckCollisionRecs(player.coll.value().boundingBox,e.coll.value().boundingBox);
            if(collision){
                collisionWithEnemy(EM, tex, speed);
            }
        }
    
    });
}


void CollisionSystem::collisionWithEnemy(EntityManager& EM, Texture2D& tex, float& speed){
    for(int i = 0; i < EM.getEntityVector().size();i++){
        EM.removeEntity(EM.getEntityVector()[i].id);
    }
    speed = 0.0f;
    tex = LoadTexture("img/end.png");
    while (!WindowShouldClose()){ //este bucle hay que cambiarlo
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexture(tex,0,0,WHITE);
        EndDrawing();
    } 
}