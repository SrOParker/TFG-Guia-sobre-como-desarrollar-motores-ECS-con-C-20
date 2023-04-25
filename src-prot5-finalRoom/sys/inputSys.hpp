#pragma once
#include <iostream>
#include "../man/manentity.hpp"

struct InputSystem{

    void update(EntityManager& EM);
    
    private:
    void keyPressed(InputCMP& input, PositionCMP& pos);
    int maskToCheck = InputCMP::mask; // | StatsCMP::mask; (we can add more with OR operation)


};