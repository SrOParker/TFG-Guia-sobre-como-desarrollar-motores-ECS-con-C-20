#pragma once
#include <iostream>
#include <vector>

#include "entity.hpp"

struct EntityManager{
    EntityManager(std::size_t size_for_entities = 10){
        entities.reserve(size_for_entities);
    }
    ~EntityManager(){
        for(Entity& e : entities){
            UnloadTexture (e.render.sprite);
        }
        entities.clear();
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