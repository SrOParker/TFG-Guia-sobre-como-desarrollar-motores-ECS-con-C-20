#include "inputSystem.hpp"

void InputSystem::update(EntityManager& EM){
    EM.forall([&](Entity&e){
        if(e.inp.has_value()){
            if (IsKeyDown(e.inp.value().KeyW) && e.phy.value().position.second > 10){
                e.phy.value().velocity.second = -200.0f * GetFrameTime();
            }
            if (IsKeyDown(e.inp.value().KeyA) && e.phy.value().position.first > 10){
                e.phy.value().velocity.first = -400.0f * GetFrameTime();
            } 
            if (IsKeyDown(e.inp.value().KeyS) && e.phy.value().position.second < 360){
                e.phy.value().velocity.second = 200.0f * GetFrameTime();
            }
            if (IsKeyDown(e.inp.value().KeyD) && e.phy.value().position.first < 620){
                e.phy.value().velocity.first = 200.0f * GetFrameTime();
            } 
        }
    });
}