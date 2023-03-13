#pragma once
#include "../man/manentity.hpp"

struct MovementSystem{
    void update(EntityManager& EM, bool& running, int& score);
    private:
    void PressKey(EntityManager& EM, Entity& e, bool& running, int& score);
    void ControlKeys();
    bool w_pressed{};
    bool s_pressed{};
};