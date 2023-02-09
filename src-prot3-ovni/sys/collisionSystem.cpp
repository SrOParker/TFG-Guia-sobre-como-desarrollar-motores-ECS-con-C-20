#include "collisionSystem.hpp"

void CollisionSystem::update(EntityManager& EM, Map& map, bool& running){
    auto& player = EM.getEntityVector()[0];
    EM.forall([&](Entity& e){
        if(e.coll.has_value() && e.id != player.id){
            bool collision = CheckCollisionRecs(player.coll.value().boundingBox,e.coll.value().boundingBox);
            if(collision){
                collisionWithEnemy(EM, map, running);
            }
        }
    
    });
}


void CollisionSystem::collisionWithEnemy(EntityManager& EM, Map& map, bool& running){

    for(int i = 0;i < (int)EM.getEntityVector().size();i++){
        EM.removeEntity(EM.getEntityVector()[i].id);
    }EM.getEntityVector().clear();


    running = false;
    map.setMapSpeed( 0.0f );
    map.setMapBackground( "img/end.png" );
    map.setMapPositions((Vector2){0,0}); 
}