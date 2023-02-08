#include "renderCMP.hpp"

RenderCMP::RenderCMP(){
    sprite = LoadTexture("img/player.png");
    box    = {0,0, (float)sprite.width, (float)sprite.height};
}