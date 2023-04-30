#pragma once

#include "man/manentity.hpp"
#include "gameManager.hpp"
#include "sys/renderSys.hpp"
#include "sys/inputSys.hpp"
#include "sys/positionSys.hpp"
#include "sys/collisionSys.hpp"
#include "sys/iaSys.hpp"
struct Game{
    
    void run();


    private:
    void createEntities();

    EntityManager EM{};
    GameManager GM{};
    
    RenderSystem rendSys{};
    InputSystem inpSys{};
    PositionSystem posSys{};
    CollisionSystem collSys{};
    IASystem iaSys{};

    bool  turn          = true;
    float time          = 0.5;
    float turn_seconds  = 0.0;
};