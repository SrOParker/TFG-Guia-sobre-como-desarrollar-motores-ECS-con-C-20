#pragma once

#include <vector>
#include "entity.hpp"
struct EntityManager{

    EntityManager(std::size_t size_for_entities = 10){
        entities.reserve(size_for_entities);
    }
    auto& createEntity(){ return entities.emplace_back();}
    void forall(auto&& function){
        for(auto&e:entities){
            function(e);
        }
    }
    std::vector<Entity>& getEntityVector(){
        return entities;
    }
    private:    
    std::vector<Entity>  entities;
};