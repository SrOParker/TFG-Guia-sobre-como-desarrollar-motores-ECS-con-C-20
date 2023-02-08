#include "man/manentity.hpp"
#include "sys/physicSystem.hpp"
#include "sys/renderSystem.hpp"
#include "sys/inputSystem.hpp"
#include "sys/collisionSystem.hpp"

struct Game{
    void run(){
        createPlayer();
        
        //Map
        float map_x = 0.0f;
        float map_y = 0.0f;
        float speed = 4.0f;
        Texture2D background = LoadTexture("img/background.png");
        
        SetTargetFPS(60);
        while (!WindowShouldClose()){
            BeginDrawing();
                ClearBackground(RAYWHITE);
                
                drawAndMoveMap(background, map_x, map_y, speed);
                rend_sys.update(EM);
                phy_sys.update(EM);
                inp_sys.update(EM);
                coll_sys.update(EM, background, speed);
                enemySpawn();
                
            EndDrawing();
        }
        textureCleaner(background);
    }
    private:
    //Entity Manager
    EntityManager EM{};
    //Systems
    CollisionSystem coll_sys{};
    PhysicSystem phy_sys{};
    RenderSystem rend_sys{};
    InputSystem inp_sys{};
    //Enemy time to spawn
    int spawnRatio=50;
    int spawn = spawnRatio;

    void createPlayer(){
        auto& player = EM.createEntity();
        player.phy = PhysicCMP();
        player.rend= RenderCMP();
        player.inp= InputCMP();
        player.coll=CollisionCMP();
    }
    void enemySpawn(){
        if (spawn == 0){
            createEnemy();
            spawn = spawnRatio;
        }spawn--;
    }
    void createEnemy(){
        
        auto& enemy= EM.createEntity();
        enemy.phy = PhysicCMP();
        enemy.rend= RenderCMP();
        enemy.coll= CollisionCMP();
        enemy.phy.value().position.first = 700;
        enemy.phy.value().position.second = 20 + (rand()%370);
        enemy.phy.value().velocity.first = (-1) * (8 + rand() % 15);
        enemy.rend.value().sprite = LoadTexture("img/enemy.png");
        enemy.rend.value().box = {0,0, (float)enemy.rend.value().sprite.width, (float)enemy.rend.value().sprite.height};
        
    } 
    void drawAndMoveMap(Texture2D& tex, float& map_x, float& map_y, float& speed){
        map_x -= speed;
        if (map_x <= -tex.width) map_x = 0;
        DrawTextureEx(tex, Vector2{map_x,map_y}, 0.0f, 1.0f, WHITE);
        DrawTextureEx(tex, Vector2{map_x + tex.width, map_y}, 0.0f, 1.0f, WHITE);
    }
    void textureCleaner(Texture2D& tex){
        UnloadTexture(tex);
    }

};