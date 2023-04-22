#pragma once
#include <iostream>
#include "../man/manentity.hpp"

struct RenderSystem{

    int maskToCheck = RenderCMP::mask; //we can add more with AND operation
    void update(EntityManager& EM){
        EM.forallMatching([&](Entity&e){
            
        }, maskToCheck);
    }
};