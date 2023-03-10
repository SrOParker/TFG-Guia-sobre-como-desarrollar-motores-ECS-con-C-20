#pragma once
#include <raylib.h>

struct RenderComponent{
    RenderComponent();
    Texture2D sprite;
    Rectangle box;
};