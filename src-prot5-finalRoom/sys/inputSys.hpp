#pragma once
#include <iostream>
#include "../man/manentity.hpp"
struct Pressed{ 
    bool w_pressed{false};
    bool a_pressed{false};
    bool s_pressed{false};
    bool d_pressed{false};

    void ControlKeys();
};

struct InputSystem{

    void update(EntityManager& EM);
    
    private:
    void keyPressed(InputCMP& input, PositionCMP& pos);
    
    Pressed controlKeys{};
    int cmpMaskToCheck = InputCMP::mask; // | StatsCMP::mask; (we can add more with OR operation)
    int tagMaskToCheck = Tags::player;
};