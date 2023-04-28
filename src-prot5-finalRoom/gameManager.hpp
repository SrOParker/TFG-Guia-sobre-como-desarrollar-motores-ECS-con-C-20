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
            generateRandomMatrix(15,15);
            generateLvl(EM,random_lvl);
            break;
        default:
            break;
        }
    }

    private:
    void generateLvl(EntityManager& EM, const int matrix_lvl[SIZELVL][SIZELVL]){
        //Create lvl
        for (int i = 0; i < 15;i++){
            for(int j = 0; j < 15; j++){
                if (matrix_lvl[i][j] == 2){
                    auto& rock_wall = EM.createEntity();
                    rock_wall.addTag(Tags::wall | Tags::collisionable);
                    EM.getCMPStorage().addRenderCMP(RenderCMP{"sprites/piedra_2.png"}, rock_wall);
                    EM.getCMPStorage().addPositionCMP(PositionCMP{j,i,0,0}, rock_wall);
                    EM.getCMPStorage().addStatsCMP(StatsCMP{6,0,0,0,0}, rock_wall);
                }else if(matrix_lvl[i][j] == 1){
                    auto& rock_wall = EM.createEntity();
                    rock_wall.addTag(Tags::wall | Tags::collisionable);
                    EM.getCMPStorage().addRenderCMP(RenderCMP{"sprites/piedra_1.png"}, rock_wall);
                    EM.getCMPStorage().addPositionCMP(PositionCMP{j,i,0,0}, rock_wall);
                    EM.getCMPStorage().addStatsCMP(StatsCMP{3,0,0,0,0}, rock_wall);
                }else if(!player_alive && matrix_lvl[i][j] == 0){
                    createPlayer(EM,j,i);
                }else if(matrix_lvl[i][j] == 3){
                    Entity& enemy = createEnemy(EM,3);
                    auto& pos = EM.getCMPStorage().getPositionCMP(enemy);
                    pos.posX = j; pos.posY = i;

                }else if(matrix_lvl[i][j] == 4){
                    Entity& enemy = createEnemy(EM,4);
                    auto& pos = EM.getCMPStorage().getPositionCMP(enemy);
                    pos.posX = j; pos.posY = i;
                }
            }
        }
    }
    
    //First Parameter high is too many rocks of type 1
    //Second Parameter high is too many rocks of type 2
    void generateRandomMatrix(int rockProbability1, int rockProbability2){
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
    }
    
    //NIVELES
    const int map_lvl1[SIZELVL][SIZELVL]{{0,0,0,0,0,0,0,0,0,1,1,2,2,0,0},
                                         {1,1,1,2,0,0,0,0,0,0,0,0,0,0,1},
                                         {0,0,1,2,0,0,0,0,0,0,0,0,0,0,1},
                                         {0,0,1,2,0,0,0,0,0,0,0,0,0,0,2},
                                         {4,0,0,0,0,0,1,1,0,0,3,0,0,0,1},
                                         {0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
                                         {0,0,0,2,2,2,2,2,2,2,2,2,0,0,0},
                                         {0,1,0,2,1,2,0,0,0,0,1,0,0,0,1},
                                         {0,1,0,2,1,1,0,0,0,0,1,0,0,0,0},
                                         {0,1,0,2,0,2,3,0,0,0,2,0,0,0,1},
                                         {0,1,0,1,0,1,0,0,0,0,2,0,0,0,0},
                                         {0,1,0,1,0,2,0,0,0,0,1,0,0,0,0},
                                         {0,0,0,0,0,0,0,0,0,0,1,0,2,2,2},
                                         {0,0,1,1,1,1,0,0,0,0,0,0,2,0,1},
                                         {0,0,0,0,0,0,4,0,0,0,0,0,2,1,0}
                                        };
    int random_lvl[SIZELVL][SIZELVL]{};
    
    void createPlayer(EntityManager& EM, int x, int y){
        auto& player = EM.createEntity();
        player.addTag(Tags::player | Tags::movement | Tags::collider);
        EM.getCMPStorage().addRenderCMP(RenderCMP{"sprites/player.png"}, player);
        EM.getCMPStorage().addPositionCMP(PositionCMP{x,y}, player);
        EM.getCMPStorage().addInputCMP(InputCMP{}, player);
        EM.getCMPStorage().addStatsCMP(StatsCMP{3,1,1,5,1}, player);

        player_alive=true;
    }
    //PLAYER
    bool player_alive=false;

    //ENEMIES
    Entity& createEnemy(EntityManager& EM, int type){
        auto& enemy = EM.createEntity();
        enemy.hasTag(Tags::collider | Tags::collisionable | Tags::enemy | Tags::movement);
        EM.getCMPStorage().addPositionCMP(PositionCMP{0,0,0,0}, enemy);

        switch (type)
        {
        case 3: // FANTASMA
            EM.getCMPStorage().addRenderCMP(RenderCMP{"sprites/enemigo_1.png"}, enemy);
            EM.getCMPStorage().addStatsCMP(StatsCMP{1, 1, 1, 1, 0}, enemy);
            break;
        case 4: // GUERRERO
            EM.getCMPStorage().addRenderCMP(RenderCMP{"sprites/enemigo_2.png"}, enemy);
            EM.getCMPStorage().addStatsCMP(StatsCMP{2, 2, 1, 1, 0}, enemy);
            break;
        default:
            break;
        }
        return enemy;
    }
};