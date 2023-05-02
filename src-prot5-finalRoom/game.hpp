#pragma once

#include "man/manentity.hpp"
#include "gameManager.hpp"
#include "sys/renderSys.hpp"
#include "sys/inputSys.hpp"
#include "sys/positionSys.hpp"
#include "sys/collisionSys.hpp"
#include "sys/iaSys.hpp"
#include "states.hpp"
struct Game{
    
    void run();
    void reset(int config);
    void startNormalGame(Map& map);
    private:
    EntityManager EM{100};
    GameManager GM{};
    
    RenderSystem rendSys{};
    InputSystem inpSys{};
    PositionSystem posSys{};
    CollisionSystem collSys{};
    IASystem iaSys{};
    States state{States::MENU};
    int   lvlActual     = 0;
    bool  playing_lvl   = false;
    bool  turn          = true;
    float time          = 0.25;
    float turn_seconds  = 0.0;
};