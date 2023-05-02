#pragma once
#include <iostream>
#include "../man/manentity.hpp"
#include "../states.hpp"
struct InputSystem{

    void update(EntityManager& EM, bool& turn, bool& playing_lvl, States& state);
    void menuKeys( int config , States& state);
    private:
    void keyPressed(EntityManager& EM, Entity& e, bool& turn, bool& playing_lvl, States& state);
    
    int cmpMaskToCheck = InputCMP::mask; // | StatsCMP::mask; (we can add more with OR operation)
    int tagMaskToCheck = Tags::player;
};