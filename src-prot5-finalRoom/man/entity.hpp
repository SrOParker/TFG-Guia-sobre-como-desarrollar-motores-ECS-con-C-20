#pragma once
#include <iostream>
#include "utils/slotmap.hpp"
#include "../cmp/components.hpp"
#include "manentity.hpp"

struct Entity{
    int cmpMask{0b0};
    int tagMask{0b0};
    Slotmap<RenderCMP>::key_type renderKey;
    Slotmap<PositionCMP>::key_type positionKey;
    Slotmap<StatsCMP>::key_type statsKey;

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
};