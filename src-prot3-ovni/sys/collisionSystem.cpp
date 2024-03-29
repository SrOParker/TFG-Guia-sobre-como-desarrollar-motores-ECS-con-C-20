#include "collisionSystem.hpp"

void CollisionSystem::update(EntityManager& EM, Map& map, States& state){
    auto& player = EM.getEntityVector()[0];
    EM.forall([&](Entity& e){
        if (e.coll.has_value()){
            e.coll.value().boundingBox = {
            e.phy.value().position.first, 
            e.phy.value().position.second, 
            static_cast<float>(e.rend.value().sprite.width), 
            static_cast<float>(e.rend.value().sprite.height)
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
    state = States::end;
    map.setMapSpeed( 0.0f );

    for(std::size_t i=0; i<EM.getEntityVector().size();i++){
        EM.getEntityVector()[i].phy.value().velocity.first = 0;
    }
}