
#include "renderComponent.hpp"


RenderComponent::RenderComponent(){
    sprite = LoadTexture("img/bombero.png");
    box    = {0,0, static_cast<float>(sprite.width), static_cast<float>(sprite.height)};
}