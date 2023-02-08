#include "physicSystem.hpp"
#include "../cmp/physicCMP.hpp"
void PhysicSystem::update(EntityManager& EM){
    EM.forall([&](Entity&e){
        if(e.phy.has_value()){
            // entity pos x += entity velocity x
            e.phy.value().position.first += e.phy.value().velocity.first;
            // entity pos y += entity velocity y
            e.phy.value().position.second += e.phy.value().velocity.second;
        }
    });
}