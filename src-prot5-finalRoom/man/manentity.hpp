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

    void forallMatching(auto&& function, int systemCMPmask, int systemTAGmask){
        for(auto&e:entities){
            if(((e.cmpMask & systemCMPmask) == systemCMPmask) && 
               ((e.tagMask & systemTAGmask) == systemTAGmask)){
                function(e);
            }
        }
    }

    void removeEntity(Entity& e) {
        //Elimina todos los componentes de una entidad
        removeAllComponents(e);
        //Eliminar entidad
        auto it = std::remove_if(entities.begin(), entities.end(), [e](Entity &ent) {
            return e == ent;
        });
        entities.erase(it, entities.end());
    }
    void removeAllComponents(Entity& e){
        CS.removeInputCMP(e);
        CS.removePositionCMP(e);
        CS.removeRenderCMP(e);
        CS.removeStatsCMP(e);
    }
    void removeAllEntities(){
        for(int i = 0;i < (int)entities.size();i++){
            removeEntity(entities[i]);
        }entities.clear();
    }
    
    Entity& getPlayer(){
        for (Entity& e: entities){
            if(e.hasTag(Tags::player)){
                return e;
            } 
        }

        throw std::runtime_error(" No player created ");
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
