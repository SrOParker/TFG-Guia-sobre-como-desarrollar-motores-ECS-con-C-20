#pragma once

#include "utils/slotmap.hpp"
#include "../cmp/components.hpp"
#include "entity.hpp"


struct ComponentStorage{

    // RENDER STORAGE
    void addRenderCMP(RenderCMP& cmp, Entity& e){
        addRenderCMP(RenderCMP{ cmp }, e);
    }
    void addRenderCMP(RenderCMP&& cmp, Entity& e){
        //Comprobamos que esa entidad no tenga ese componente ya
        if(!e.hasComponent(RenderCMP::mask)){
            //Añadimos el componente al slotmap y guardamos la llave en la entidad
            e.renderKey = renderStorage.push_back(cmp);
            //actualizamos la máscara de la entidad
            e.cmpMask = e.cmpMask | cmp.mask;
        }else{
            //Si tiene ese componente lo modificamos y se lo actualizamos
            auto& cmpRender = renderStorage[e.renderKey];
            cmpRender = cmp;
        }
    }
    RenderCMP& getRenderCMP(Entity& e){
        if(!e.hasComponent(RenderCMP::mask)) throw std::runtime_error(" RenderCMP no existe ");
        return renderStorage[e.renderKey];  
    }
    bool removeRenderCMP(Entity& e){
        if(e.hasComponent(RenderCMP::mask)){
            //Eliminamos el componente de render
            renderStorage.erase(e.renderKey);
            //Actualizamos la mascara de la entidad
            e.cmpMask = e.cmpMask xor RenderCMP::mask;
            //ELiminamos la key de la entidad
            e.renderKey.id = 0;
            e.renderKey.gen= 0;
            return true;
        }
        return false;
    }
    Slotmap<RenderCMP> renderStorage{};

    // POSITION STORAGE
    void addPositionCMP(PositionCMP& cmp, Entity& e){
        addPositionCMP(PositionCMP{ cmp }, e);
    }
    void addPositionCMP(PositionCMP&& cmp, Entity& e){
        //Comprobamos que esa entidad no tenga ese componente ya
        if(!e.hasComponent(PositionCMP::mask)){
            //Añadimos el componente al slotmap y guardamos la llave en la entidad
            e.positionKey = positionStorage.push_back(cmp);
            //actualizamos la máscara de la entidad
            e.cmpMask = e.cmpMask | cmp.mask;
        }else{
            //Si tiene ese componente lo modificamos y se lo actualizamos
            auto& cmpposition = positionStorage[e.positionKey];
            cmpposition = cmp;
        }
    }
    PositionCMP& getPositionCMP(Entity& e){
        if(!e.hasComponent(PositionCMP::mask)) throw std::runtime_error(" PositionCMP no existe ");
        return positionStorage[e.positionKey];  
    }
    bool removePositionCMP(Entity& e){
        if(e.hasComponent(PositionCMP::mask)){
            //Eliminamos el componente de posicion
            positionStorage.erase(e.positionKey);
            //Actualizamos la mascara de la entidad
            e.cmpMask = e.cmpMask xor PositionCMP::mask;
            //ELiminamos la key de la entidad
            e.positionKey.id = 0;
            e.positionKey.gen= 0;
            return true;
        }
        return false;
    }
    Slotmap<PositionCMP> positionStorage{};

    // STATS STORAGE
    void addStatsCMP(StatsCMP& cmp, Entity& e){
        addStatsCMP(StatsCMP{ cmp }, e);
    }
    void addStatsCMP(StatsCMP&& cmp, Entity& e){
        //Comprobamos que esa entidad no tenga ese componente ya
        if(!e.hasComponent(StatsCMP::mask)){
            //Añadimos el componente al slotmap y guardamos la llave en la entidad
            e.statsKey = statsStorage.push_back(cmp);
            //actualizamos la máscara de la entidad
            e.cmpMask = e.cmpMask | cmp.mask;
        }else{
            //Si tiene ese componente lo modificamos y se lo actualizamos
            auto& cmpposition = statsStorage[e.statsKey];
            cmpposition = cmp;
        }
    }
    StatsCMP& getStatsCMP(Entity& e){
        if(!e.hasComponent(StatsCMP::mask)) throw std::runtime_error(" StatsCMP no existe ");
        return statsStorage[e.statsKey];  
    }
    bool removeStatsCMP(Entity& e){
        if(e.hasComponent(StatsCMP::mask)){
            //Eliminamos el componente de posicion
            statsStorage.erase(e.statsKey);
            //Actualizamos la mascara de la entidad
            e.cmpMask = e.cmpMask xor StatsCMP::mask;
            //ELiminamos la key de la entidad
            e.statsKey.id = 0;
            e.statsKey.gen= 0;
            return true;
        }
        return false;
    }
    Slotmap<StatsCMP> statsStorage{};

};