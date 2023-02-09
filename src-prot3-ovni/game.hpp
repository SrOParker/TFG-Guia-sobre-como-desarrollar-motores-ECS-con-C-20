#include "man/manentity.hpp"
#include "sys/physicSystem.hpp"
#include "sys/renderSystem.hpp"
#include "sys/inputSystem.hpp"
#include "sys/collisionSystem.hpp"
#include "map.hpp"

struct Game{
    Game(){
        EM =  EntityManager();
        coll_sys = CollisionSystem();
        phy_sys = PhysicSystem();
        rend_sys = RenderSystem();
        inp_sys = InputSystem();
        spawnRatio=45;
        spawn = spawnRatio;
        running = true;
        score = 0.0f;
    }

    void run(){
        createPlayer();
        map.setMapBackground("img/background.png");
        SetTargetFPS(60);
        while (!WindowShouldClose()){
            BeginDrawing();
            ClearBackground(RAYWHITE);
            map.drawAndMoveMap();
            if(running){

                rend_sys.update(EM, score);
                phy_sys.update(EM);
                inp_sys.update(EM);
                coll_sys.update(EM, map, running);
                enemySpawn();
                score+= 0.1f;
            }else{
                rend_sys.printText(score);
                replay(map);
            }
            EndDrawing();
        }map.textureCleaner(map.getMapBackground());
    }
    private:
    //Entity Manager
    EntityManager EM;
    //Systems
    CollisionSystem coll_sys;
    PhysicSystem phy_sys;
    RenderSystem rend_sys;
    InputSystem inp_sys;
    //Mapa
    Map map;
    //Enemy time to spawn
    int spawnRatio;
    int spawn;
    bool running;
    float score;

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

    void replay(Map& map){
        if (IsKeyDown(KEY_SPACE)){
            score = 0.0f;
            running = true;
            createPlayer();

            map.setMapSpeed(4.0f);
            map.setMapBackground("img/background.png");
        }
    }
};