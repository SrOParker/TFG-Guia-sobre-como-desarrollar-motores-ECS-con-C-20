#include "physicSystem.hpp"
#include "../cmp/physicCMP.hpp"
void PhysicSystem::update(EntityManager& EM){
    auto& player = EM.getEntityVector()[0];
    EM.forall([&](Entity&e){
        if(e.phy.has_value()){
            // entity pos x += entity velocity x
            e.phy.value().position.first += e.phy.value().velocity.first;
            // entity pos y += entity velocity y
            e.phy.value().position.second += e.phy.value().velocity.second;
            if(e.id == player.id){
                e.phy.value().velocity.first = 0;
                e.phy.value().velocity.second = 0;
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