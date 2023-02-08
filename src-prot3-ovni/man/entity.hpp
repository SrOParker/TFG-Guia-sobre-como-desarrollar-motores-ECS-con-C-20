#pragma once

#include "../cmp/physicCMP.hpp"
#include "../cmp/renderCMP.hpp"
#include "../cmp/inputCMP.hpp"
#include "../cmp/collisionCMP.hpp"
#include <iostream>
#include <optional>
struct Entity{
    
    Entity();

    int id;
    std::optional<CollisionCMP> coll;
    std::optional<InputCMP> inp;
    std::optional<RenderCMP> rend;
    std::optional<PhysicCMP> phy;
    
    private:

    inline static int nextID{1};

};