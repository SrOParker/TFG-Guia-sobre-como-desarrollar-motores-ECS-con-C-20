#pragma once

#include "utils/slotmap.hpp"
#include "../cmp/components.hpp"
#include "entity.hpp"
struct ComponentStorage{
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
};