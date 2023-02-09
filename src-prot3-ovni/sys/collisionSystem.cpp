#include "collisionSystem.hpp"

void CollisionSystem::update(EntityManager& EM, Texture2D& tex, float& speed, bool& running){
    auto& player = EM.getEntityVector()[0];
    EM.forall([&](Entity& e){
        if(e.coll.has_value() && e.id != player.id){
            bool collision = CheckCollisionRecs(player.coll.value().boundingBox,e.coll.value().boundingBox);
            if(collision){
                collisionWithEnemy(EM, tex, speed, running);
            }
        }
    
    });
}


void CollisionSystem::collisionWithEnemy(EntityManager& EM, Texture2D& tex, float& speed, bool& running){

    for(int i = 0;i < (int)EM.getEntityVector().size();i++){
        EM.removeEntity(EM.getEntityVector()[i].id);
    }EM.getEntityVector().clear();

    speed = 0.0f;
    tex = LoadTexture("img/end.png");
    
    
    DrawTexture(tex,0,0,WHITE);
    running = false;
    
}