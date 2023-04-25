#pragma once

#include "man/manentity.hpp"
#include "sys/renderSys.hpp"

struct Game{
    
    void run();


    private:
    void createEntities();

    EntityManager EM{};
    RenderSystem rendSys{};
};