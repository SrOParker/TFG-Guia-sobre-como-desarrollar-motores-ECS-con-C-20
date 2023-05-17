#include "renderCMP.hpp"

RenderCMP::RenderCMP(){
    sprite = LoadTexture("img/player.png");
    box    = {0,0, static_cast<float>(sprite.width), static_cast<float>(sprite.height)};
}


