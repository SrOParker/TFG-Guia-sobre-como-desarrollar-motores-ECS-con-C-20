#pragma once

#include "../cmp/physicCMP.hpp"
#include "../cmp/renderCMP.hpp"
#include <iostream>
#include <optional>
struct Entity{
    
    Entity();

    int id;
    std::optional<RenderCMP> rend;
    std::optional<PhysicCMP> phy;
    
    private:

    inline static int nextID{1};

};