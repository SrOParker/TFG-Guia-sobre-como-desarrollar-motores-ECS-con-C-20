#pragma once

#include "man/manentity.hpp"
#include "gameManager.hpp"
#include "sys/renderSys.hpp"
#include "sys/inputSys.hpp"
#include "sys/positionSys.hpp"
#include "sys/collisionSys.hpp"
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
};