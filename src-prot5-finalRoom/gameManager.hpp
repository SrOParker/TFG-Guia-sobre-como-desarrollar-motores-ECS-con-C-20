#pragma once

#include <iostream>
#include "man/manentity.hpp"

#define SIZELVL 15
struct GameManager{
    enum LvlNumber{
        Lvl0,
        Lvl1,
        Random
    };
    
    void selectLvlAndGenerate(EntityManager& EM, int lvl){
        switch (lvl)
        {
        case LvlNumber::Lvl0:
            /* code */
            break;
        case LvlNumber::Lvl1:
            generateLvl(EM, map_lvl1);
            break;
        case LvlNumber::Random:
            generateRandomMatrix(15,15,2,2);
            generateLvl(EM,random_lvl);
            break;
        default:
            break;
        }
    }
    auto& getActualMap(){
        return actual_lvl;
    }
    Entity& createObject(EntityManager& EM, int obj){
        Entity& entity = EM.createEntity();
        entity.addTag(Tags::object);

        switch (obj)
        {
        case Objects::Health :
            EM.getCMPStorage().addRenderCMP(RenderCMP{"sprites/vida.png"}, entity);
            EM.getCMPStorage().addStatsCMP(StatsCMP{1,1,0,0,0,0}, entity);
            break;
        case Objects::Damage : 
            EM.getCMPStorage().addRenderCMP(RenderCMP{"sprites/ataque.png"}, entity);
            EM.getCMPStorage().addStatsCMP(StatsCMP{0,0,1,0,0,0}, entity);
            break;
        case Objects::Steps :
            EM.getCMPStorage().addRenderCMP(RenderCMP{"sprites/velocidad.png"}, entity);
            EM.getCMPStorage().addStatsCMP(StatsCMP{0,0,0,1,0,0}, entity);
            break;
        case Objects::Critical : 
            EM.getCMPStorage().addRenderCMP(RenderCMP{"sprites/critico.png"}, entity);
            EM.getCMPStorage().addStatsCMP(StatsCMP{0,0,0,0,1,0}, entity);
            break;
        case Objects::Pickaxe :
            EM.getCMPStorage().addRenderCMP(RenderCMP{"sprites/pico.png"}, entity);
            EM.getCMPStorage().addStatsCMP(StatsCMP{0,0,0,0,0,1}, entity);
            break;
        default:
            break;
        }
        return entity;
    }
    private:
    //NIVELES    
    void generateLvl(EntityManager& EM, const int matrix_lvl[SIZELVL][SIZELVL]){
        
        //Create lvl
        for (int i = 0; i < 15;i++){
            for(int j = 0; j < 15; j++){
                if (matrix_lvl[i][j] == 1){
                    auto& rock_wall = EM.createEntity();
                    rock_wall.addTag(Tags::wall | Tags::collisionable);
                    EM.getCMPStorage().addRenderCMP(RenderCMP{"sprites/piedra_2-sheet.png"}, rock_wall);
                    EM.getCMPStorage().addPositionCMP(PositionCMP{j,i,0,0}, rock_wall);
                    EM.getCMPStorage().addStatsCMP(StatsCMP{4,4,0,0,0,0}, rock_wall);

                    actual_lvl[i][j]=2;
                }else if(matrix_lvl[i][j] == 2){
                    auto& rock_wall = EM.createEntity();
                    rock_wall.addTag(Tags::wall | Tags::collisionable);
                    EM.getCMPStorage().addRenderCMP(RenderCMP{"sprites/piedra_1-sheet.png"}, rock_wall);
                    EM.getCMPStorage().addPositionCMP(PositionCMP{j,i,0,0}, rock_wall);
                    EM.getCMPStorage().addStatsCMP(StatsCMP{4,4,0,0,0,0}, rock_wall);

                    actual_lvl[i][j]=1;
                }else if(!player_alive && matrix_lvl[i][j] == 0){
                    createPlayer(EM,j,i);

                    actual_lvl[i][j]=0;
                }else if(matrix_lvl[i][j] == 3){
                    Entity& enemy = createEnemy(EM,3);
                    auto& pos = EM.getCMPStorage().getPositionCMP(enemy);
                    pos.posX = j; pos.posY = i;

                }else if(matrix_lvl[i][j] == 4){
                    Entity& enemy = createEnemy(EM,4);
                    auto& pos = EM.getCMPStorage().getPositionCMP(enemy);
                    pos.posX = j; pos.posY = i;
                }else if(matrix_lvl[i][j] == 5){
                    createChest(EM,i,j);
                }else{
                    actual_lvl[i][j] = 0;
                }
            }
        }
    }
    void generateRandomMatrix(int rockProbability1, int rockProbability2, int numEnemy3, int numEnemy4){
        
        for (int i = 0; i < 15;i++){
            for(int j = 0; j < 15; j++){
                int num = rand()%100;
                if (num < 1 + rockProbability1){
                    random_lvl[j][i] = 1;   
                }else if(num > 100 - rockProbability2){
                    random_lvl[j][i] = 2;
                }
            }
        }

        bool chest = false;
        while(!chest){
            int num  = rand() % 15;
            int num2 = rand() % 15;
            if(random_lvl[num][num2]== 0){
                random_lvl[num][num2] = 5;
                chest=true;

            } 
        }

        int x{},y{}, enemies3{}, enemies4{};
        while(numEnemy3 != enemies3 || numEnemy4 != enemies4){
            x = rand() % 15;
            y = rand() % 15;
            if(numEnemy3 != enemies3 && random_lvl[x][y] == 0){
                random_lvl[x][y] = 3;
                enemies3 ++;
            }
            x = rand() % 15;
            y = rand() % 15;
            if(numEnemy4 != enemies4 && random_lvl[x][y] == 0){
                random_lvl[x][y] = 4;
                enemies4 ++;
            }
        }
    }
    const int map_lvl1[SIZELVL][SIZELVL]{{0,0,0,0,0,0,5,0,0,1,1,2,2,0,0},
                                         {1,1,1,2,0,0,0,0,0,0,0,0,0,0,1},
                                         {0,0,1,2,0,0,0,0,0,0,0,0,0,0,1},
                                         {0,0,1,2,0,0,0,0,0,0,0,0,0,0,2},
                                         {4,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
                                         {0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
                                         {0,0,0,2,2,2,2,2,2,2,2,2,0,0,0},
                                         {0,1,0,2,1,2,0,0,0,0,1,0,0,0,1},
                                         {0,1,0,2,1,1,0,0,0,0,1,0,0,0,0},
                                         {0,1,0,2,0,2,0,0,0,0,2,0,0,0,1},
                                         {0,1,0,1,0,1,0,0,0,0,2,0,0,0,0},
                                         {0,1,0,1,0,2,0,0,0,0,1,0,0,0,0},
                                         {0,0,0,0,0,0,0,0,0,0,1,0,2,2,2},
                                         {0,0,1,1,1,1,0,0,0,0,0,0,2,0,1},
                                         {0,0,0,0,0,0,0,0,0,0,0,0,2,1,0}
                                        };
    int random_lvl[SIZELVL][SIZELVL]{};
    int actual_lvl[SIZELVL][SIZELVL]{};
    //PLAYER
    void createPlayer(EntityManager& EM, int x, int y){
        auto& player = EM.createEntity();
        player.addTag(Tags::player | Tags::movement | Tags::collider | Tags::collisionable);
        EM.getCMPStorage().addRenderCMP(RenderCMP{"sprites/player.png"}, player);
        EM.getCMPStorage().addPositionCMP(PositionCMP{x,y}, player);
        EM.getCMPStorage().addInputCMP(InputCMP{}, player);
        EM.getCMPStorage().addStatsCMP(StatsCMP{3,3,1,1,5,1}, player);

        player_alive=true;
    }
    bool player_alive=false;
    //ENEMIES
    Entity& createEnemy(EntityManager& EM, int type){
        auto& enemy = EM.createEntity();
        enemy.addTag(Tags::collider | Tags::collisionable | Tags::enemy | Tags::movement);
        EM.getCMPStorage().addPositionCMP(PositionCMP{0,0,0,0}, enemy);

        switch (type)
        {
        case 3: // FANTASMA
            enemy.addTag(Tags::ghost);
            EM.getCMPStorage().addRenderCMP(RenderCMP{"sprites/enemigo_1.png"}, enemy);
            EM.getCMPStorage().addStatsCMP(StatsCMP{1, 1, 1, 1, 1, 0}, enemy);
            break;
        case 4: // SOLDADO
            enemy.addTag(Tags::soldier);
            EM.getCMPStorage().addRenderCMP(RenderCMP{"sprites/enemigo_2.png"}, enemy);
            EM.getCMPStorage().addStatsCMP(StatsCMP{2, 2, 2, 1, 1, 0}, enemy);
            break;
        default:
            break;
        }
        return enemy;
    }
    //OBJECTS
    void createChest(EntityManager& EM, int x, int y){
        auto& chest = EM.createEntity();
        chest.addTag(Tags::chest | Tags::collisionable);
        EM.getCMPStorage().addRenderCMP(RenderCMP{"sprites/chest.png"}, chest);
        EM.getCMPStorage().addPositionCMP(PositionCMP{y,x,0,0}, chest);
    }

};

