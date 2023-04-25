#pragma once
#include <iostream>
#include "../man/manentity.hpp"




struct PositionSys{

    void update(EntityManager& EM);
    
    private:
    int maskToCheck = PositionCMP::mask; // | StatsCMP::mask; (we can add more with OR operation)
};