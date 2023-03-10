
#include "renderComponent.hpp"


RenderComponent::RenderComponent(){
    sprite = LoadTexture("img/bombero.png");
    box    = {0,0, (float)sprite.width, (float)sprite.height};
}