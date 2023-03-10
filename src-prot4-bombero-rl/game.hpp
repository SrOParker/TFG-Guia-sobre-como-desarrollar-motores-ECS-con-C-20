#pragma once
#include "man/manentity.hpp"
#include "sys/movementSystem.hpp"
#include "sys/renderSystem.hpp"
struct Game{
        void run();
        
    private:
        void createEntitiesForFirefighterGameRL();
        bool checkRooms(bool& ending);
        EntityManager EM{};
        MovementSystem mov_sys{};
        RenderSystem rend_sys{}; 
};