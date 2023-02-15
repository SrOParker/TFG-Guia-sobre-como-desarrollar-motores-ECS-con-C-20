#include "collisionSystem.hpp"

void CollisionSystem::update(EntityManager& EM, Map& map, States& state){
    auto& player = EM.getEntityVector()[0];
    EM.forall([&](Entity& e){
        if (e.coll.has_value()){
            e.coll.value().boundingBox = {
            e.phy.value().position.first, 
            e.phy.value().position.second, 
            (float)e.rend.value().sprite.width, 
            (float)e.rend.value().sprite.height
            };
            if(e.id != player.id){
                bool collision = CheckCollisionRecs(player.coll.value().boundingBox,e.coll.value().boundingBox);
                if(collision){
                    collisionWithEnemy(EM, map, state);
                }
            }
        }
    });
}


void CollisionSystem::collisionWithEnemy(EntityManager& EM, Map& map, States& state){

    for(int i = 0;i < (int)EM.getEntityVector().size();i++){
        UnloadTexture(EM.getEntityVector()[i].rend.value().sprite);
        EM.removeEntity(EM.getEntityVector()[i].id);
    }EM.getEntityVector().clear();


    state = States::end;
    map.setMapSpeed( 0.0f );
    map.setMapBackground( "img/end.png" );
    map.setMapPositions((Vector2){0,0}); 
}