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
    void endGame(Map& map);
    void wikiScreen(Map& map);
    void menuScreen(Map& map, bool& running);
    private:
    EntityManager EM{100};
    GameManager GM{};
    
    RenderSystem rendSys{};
    InputSystem inpSys{};
    PositionSystem posSys{};
    CollisionSystem collSys{};
    IASystem iaSys{};
    States state{States::MENU};
    bool  playing_lvl   = false;
    bool  turn          = true;
    float time          = 0.25;
    float turn_seconds  = 0.0;
};