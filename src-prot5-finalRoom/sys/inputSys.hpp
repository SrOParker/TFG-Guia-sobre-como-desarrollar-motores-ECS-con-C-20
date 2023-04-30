#pragma once
#include <iostream>
#include "../man/manentity.hpp"

struct InputSystem{

    void update(EntityManager& EM, bool& turn);
    
    private:
    void keyPressed(InputCMP& input, PositionCMP& pos, bool& turn);
    
    int cmpMaskToCheck = InputCMP::mask; // | StatsCMP::mask; (we can add more with OR operation)
    int tagMaskToCheck = Tags::player;
};