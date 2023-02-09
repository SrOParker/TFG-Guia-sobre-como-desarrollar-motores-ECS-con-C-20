#include "man/manentity.hpp"
#include "sys/physicSystem.hpp"
#include "sys/renderSystem.hpp"
#include "sys/inputSystem.hpp"
#include "sys/collisionSystem.hpp"
#include "map.hpp"
#include "states.hpp"

#define SPAWN_NUMBER 60
#define DIFFICULTY_INCREMENT 10
struct Game{
    Game(){
        state = States::menu;
        EM =  EntityManager();
        coll_sys = CollisionSystem();
        phy_sys = PhysicSystem();
        rend_sys = RenderSystem();
        inp_sys = InputSystem();
        running = true;
        score = 0.0f;
        record=0.0f;
        
        difficulty = 1;
        spawnRatio=SPAWN_NUMBER - DIFFICULTY_INCREMENT * difficulty;
        spawn = spawnRatio;
    }

    void run(){
        map.setMapBackground("img/menu.png");
        SetTargetFPS(60);
        while (!WindowShouldClose()){
            BeginDrawing();
            ClearBackground(RAYWHITE);
            map.drawAndMoveMap();
            switch (state) {
            case States::menu:
                chooseDifficulty();
                rend_sys.printDifficultySelected(difficulty);
                rend_sys.printRecord(record);
                goToPlay();
                break;
            case States::play:
                rend_sys.update(EM, score);
                phy_sys.update(EM);
                inp_sys.update(EM);
                coll_sys.update(EM, map, state);
                enemySpawn();
                score+= 0.1f;
                break;
            case States::end:
                rend_sys.printScore(score);
                goToMenu();
                break;
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
    float record;
    int difficulty;
    //State of the game
    States state;

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

    void goToMenu(){
        if(record<score){
            record = score;
        }
        if (IsKeyDown(KEY_SPACE)){
            score = 0.0f;
            state = States::menu;
            map.setMapBackground("img/menu.png");
            spawnRatio = SPAWN_NUMBER;
        }

    }
    void goToPlay(){
        if (IsKeyDown(KEY_ENTER)){
            score = 0.0f;
            createPlayer();
            map.setMapSpeed(4.0f);
            map.setMapBackground("img/background.png");
            state = States::play;
        }
    }
    void chooseDifficulty(){
        if (IsKeyDown(KEY_ONE)){
            difficulty = 1;
            spawnRatio = SPAWN_NUMBER -DIFFICULTY_INCREMENT* difficulty;
        }
        if (IsKeyDown(KEY_TWO)){
            difficulty = 2;
            spawnRatio = SPAWN_NUMBER-DIFFICULTY_INCREMENT* difficulty;
        }
        if (IsKeyDown(KEY_THREE)){
            difficulty = 3;
            spawnRatio = SPAWN_NUMBER- DIFFICULTY_INCREMENT* difficulty;
        }
        
    }
};