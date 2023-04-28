#pragma once
#include <iostream>
#include "manentity.hpp"
#include "utils/slotmap.hpp"
#include "../cmp/components.hpp"


struct Entity{
    int cmpMask{0b0};
    int tagMask{0b0};
    Slotmap<RenderCMP>::key_type renderKey;
    Slotmap<PositionCMP>::key_type positionKey;
    Slotmap<StatsCMP>::key_type statsKey;
    Slotmap<InputCMP>::key_type inputKey;
    
    bool operator==(const Entity& e2) {
        return cmpMask == e2.cmpMask
            && tagMask == e2.tagMask
            && renderKey.gen == e2.renderKey.gen
            && renderKey.id == e2.renderKey.id
            && positionKey.gen == e2.positionKey.gen
            && positionKey.id == e2.positionKey.id
            && statsKey.gen == e2.statsKey.gen
            && statsKey.id == e2.statsKey.id
            && inputKey.gen == e2.inputKey.gen
            && inputKey.id == e2.inputKey.id;
    }
    
    bool hasComponent(int m){
        if((cmpMask & m) == m){
            return true;
        }
        return false;
    }
    bool hasTag(int t){
        if((tagMask & t) == t){
            return true;
        }
        return false;
    }

    void addTag(int tag){
        tagMask = tagMask | tag;
    }
};