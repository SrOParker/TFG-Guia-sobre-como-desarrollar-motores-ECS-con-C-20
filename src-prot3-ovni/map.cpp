#include "map.hpp"

    Map::Map(){
        map_x = 0.0f;
        map_y = 0.0f;
        speed = 0.0f;
    }


    void Map::drawAndMoveMap(){
        map_x -= speed;
        if (map_x <= -background.width) map_x = 0;
        DrawTextureEx(background, Vector2{map_x,map_y}, 0.0f, 1.0f, WHITE);
        DrawTextureEx(background, Vector2{map_x + background.width, map_y}, 0.0f, 1.0f, WHITE);
    }
    void Map::textureCleaner(Texture2D& tex){
        UnloadTexture(tex);
    }
    Vector2 Map::getMapPositions(){
        return (Vector2){map_x, map_y};
    }

    float Map::getScreenSpeed(){
        return speed;
    }
    Texture2D& Map::getMapBackground(){
        return background;
    }
    void Map::setMapPositions(Vector2 positions){
        map_x = positions.x;
        map_y = positions.y;
    }
    void Map::setMapSpeed(float sp){
        speed = sp;
    }
    void Map::setMapBackground(const char* route){
        textureCleaner(background);
        background = LoadTexture(route);
    }