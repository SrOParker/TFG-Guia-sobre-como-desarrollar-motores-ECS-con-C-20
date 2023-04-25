#pragma once

#include "man/manentity.hpp"
#include "sys/renderSys.hpp"
#include "sys/inputSys.hpp"
#include "gameManager.hpp"
struct Game{
    
    void run();


    private:
    void createEntities();

    EntityManager EM{};
    RenderSystem rendSys{};
    InputSystem inpSys{};
    GameManager GM{};
};