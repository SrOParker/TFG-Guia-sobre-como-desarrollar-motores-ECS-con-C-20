#pragma once

#include <vector>
#include <algorithm>
#include "entity.hpp"
#include "componentStorage.hpp"

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

    void forallMatching(auto&& function, int systemCMPmask){
        for(auto&e:entities){
            if((e.cmpMask & systemCMPmask) == systemCMPmask){
                function(e);
            }
        }
    }
    std::vector<Entity>& getEntityVector(){
        return entities;
    }

    ComponentStorage& getCMPStorage(){
        return CS;
    }
    private:    
    std::vector<Entity>     entities;
    ComponentStorage CS{};
};





    /* Remove entities
    void removeEntity(int id) {
        auto it = std::remove_if(entities.begin(), entities.end(), [id](const Entity &e) {
            return e.id == id;
        });
        entities.erase(it, entities.end());
    }

    void removeAllEntities(){
        for(int i = 0;i < (int)entities.size();i++){
            UnloadTexture(entities[i].rend.value().sprite);
            removeEntity(entities[i].id);
        }entities.clear();
    }*/