#include "physicSystem.hpp"
#include "../cmp/physicCMP.hpp"
void PhysicSystem::update(EntityManager& EM){
    EM.forall([&](Entity&e){
        if(e.phy.has_value()){
            // entity pos x += entity velocity x
            e.phy.value().position.first += e.phy.value().velocity.first;
            // entity pos y += entity velocity y
            e.phy.value().position.second += e.phy.value().velocity.second;

            if (e.coll.has_value()){
                e.coll.value().boundingBox = {
                    e.phy.value().position.first, 
                    e.phy.value().position.second, 
                    (float)e.rend.value().sprite.width, 
                    (float)e.rend.value().sprite.height
                };
            }
        }
        checkPositions(EM,e);
    });
}

void PhysicSystem::checkPositions(EntityManager& EM, Entity& e){
    if (e.phy.value().position.first < -20){
        EM.removeEntity(e.id);
    }
}