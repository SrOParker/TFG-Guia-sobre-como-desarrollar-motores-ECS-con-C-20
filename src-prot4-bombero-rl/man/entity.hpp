#pragma once
#include "../cmp/renderComponent.hpp"
#include "../cmp/movementComponent.hpp"
#include "../cmp/roomComponent.hpp"


struct Entity{
    bool has_render{};
    RenderComponent render{};
    
    bool has_room{};
    RoomComponent room{};
    
    bool has_movement{};
    MovementComponent movement{};
};