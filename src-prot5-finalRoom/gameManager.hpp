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
    void clearInventory(){
        inventory.clear();
    }
    void saveInventory(EntityManager& EM){
        clearInventory();
        EM.forallMatching([&](Entity& e){
            int type_of_cmp = EM.getCMPStorage().getObjectCMP(e).obj;
            inventory.push_back(type_of_cmp);
        }, ObjectCMP::mask, Tags::object);
    }
    void killPlayer(){
        player_alive = false;
    }
    void selectLvlAndGenerate(EntityManager& EM, int lvl){
        clearMatrix();
        switch (lvl)
        {
        case LvlNumber::Lvl0:
            /* code */
            generateLvl(EM, map_lvl0);
            break;
        case LvlNumber::Lvl1:
            generateLvl(EM, map_lvl1);
            break;
        case LvlNumber::Random:
            generateRandomMatrix(lvl);
            generateLvl(EM, random_lvl);
            break;
        default:
            generateRandomMatrix(lvl);
            generateLvl(EM, random_lvl);
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
            EM.getCMPStorage().addObjectCMP(ObjectCMP{Objects::Health},entity);
            break;
        case Objects::Damage : 
            EM.getCMPStorage().addRenderCMP(RenderCMP{"sprites/ataque.png"}, entity);
            EM.getCMPStorage().addStatsCMP(StatsCMP{0,0,1,0,0,0}, entity);
            EM.getCMPStorage().addObjectCMP(ObjectCMP{Objects::Damage},entity);
            break;
        case Objects::Steps :
            EM.getCMPStorage().addRenderCMP(RenderCMP{"sprites/velocidad.png"}, entity);
            EM.getCMPStorage().addStatsCMP(StatsCMP{0,0,0,1,0,0}, entity);
            EM.getCMPStorage().addObjectCMP(ObjectCMP{Objects::Steps},entity);
            break;
        case Objects::Critical : 
            EM.getCMPStorage().addRenderCMP(RenderCMP{"sprites/critico.png"}, entity);
            EM.getCMPStorage().addStatsCMP(StatsCMP{0,0,0,0,1,0}, entity);
            EM.getCMPStorage().addObjectCMP(ObjectCMP{Objects::Critical},entity);
            break;
        case Objects::Pickaxe :
            EM.getCMPStorage().addRenderCMP(RenderCMP{"sprites/pico.png"}, entity);
            EM.getCMPStorage().addStatsCMP(StatsCMP{0,0,0,0,0,1}, entity);
            EM.getCMPStorage().addObjectCMP(ObjectCMP{Objects::Pickaxe},entity);
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

                    actual_lvl[i][j]=1;
                }else if(matrix_lvl[i][j] == 2){
                    auto& rock_wall = EM.createEntity();
                    rock_wall.addTag(Tags::wall | Tags::collisionable);
                    EM.getCMPStorage().addRenderCMP(RenderCMP{"sprites/piedra_1-sheet.png"}, rock_wall);
                    EM.getCMPStorage().addPositionCMP(PositionCMP{j,i,0,0}, rock_wall);
                    EM.getCMPStorage().addStatsCMP(StatsCMP{4,4,0,0,0,0}, rock_wall);

                    actual_lvl[i][j]=2;
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
                    actual_lvl[i][j]=5;
                }else if(matrix_lvl[i][j] == 6){
                    createKey(EM,i,j);
                    actual_lvl[i][j]=6;
                }else if(matrix_lvl[i][j] == 7){
                    createDoor(EM,i,j);
                    actual_lvl[i][j]=7;
                }else{
                    actual_lvl[i][j] = 0;
                }
            }
        }
    }
    void generateRandomMatrix(int lvl){
        //////////////////////////////////////////////
        //rockProbability1 >>>> more rocks of type 1//
        //rockProbability2 >>>> more rocks of type 2//
        //numEnemy3        >>>> more enemies of ty 3//
        //numEnemy4        >>>> more enemies of ty 4//
        //////////////////////////////////////////////
        int rockProbability1{15}, rockProbability2{15}, numEnemy3{3}, numEnemy4{2};
        if (lvl>=4 && lvl<=6){
            rockProbability1 += 2;
            rockProbability2 += 2;
            numEnemy3 ++;
            numEnemy4 ++; 
        }else if( lvl>6 && lvl<=8 ){
            rockProbability1 += 4;
            rockProbability2 += 4;
            numEnemy3 +=2;
            numEnemy4 +=2; 
        }else if(lvl>8){
            rockProbability1 = 22;
            rockProbability2 = 22;
            numEnemy3 = 7;
            numEnemy4 = 5;
        }
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

        bool door = false;
        while(!door){
            int num  = rand() % 15;
            int num2 = rand() % 15;
            if(random_lvl[num][num2] == 0){
                random_lvl[num][num2] = 7;
                door=true;
            } 
        }
        bool key = false;
        while(!key){
            int num  = rand() % 15;
            int num2 = rand() % 15;
            if(random_lvl[num][num2] == 0){
                random_lvl[num][num2] = 6;
                key=true;
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
    const int map_lvl0[SIZELVL][SIZELVL]{{0,0,0,0,0,0,0,2,2,2,2,0,0,0,0},
                                         {1,2,1,1,0,0,0,0,0,0,0,0,0,0,0},
                                         {1,3,0,0,0,0,0,0,0,0,2,2,0,0,0},
                                         {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                         {1,0,1,2,2,2,0,0,0,0,0,0,1,2,6},
                                         {1,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
                                         {0,0,0,0,0,0,0,0,1,1,1,0,1,2,3},
                                         {0,0,0,0,0,2,2,2,2,0,0,0,0,0,0},
                                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                         {1,1,1,0,0,1,2,2,1,0,0,0,0,0,0},
                                         {1,2,2,0,0,1,2,1,1,0,0,0,0,0,0},
                                         {0,1,0,0,0,0,0,0,0,0,0,0,2,2,0},
                                         {0,0,0,0,0,0,0,0,0,0,0,0,2,7,0},
                                         {1,1,1,0,0,1,1,1,0,0,1,1,1,0,0}};
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
                                         {0,0,1,1,1,1,0,0,0,0,0,0,2,6,1},
                                         {0,0,0,0,0,0,0,0,0,0,0,0,2,1,7}
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
    std::vector<int> inventory{};
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
    void createKey(EntityManager& EM, int x, int y){
        auto& key = EM.createEntity();
        key.addTag(Tags::collisionable | Tags::key);
        EM.getCMPStorage().addRenderCMP(RenderCMP{"sprites/llave.png"}, key);
        EM.getCMPStorage().addPositionCMP(PositionCMP{y,x,0,0}, key);
    }
    void createDoor(EntityManager& EM, int x, int y){
        auto& door = EM.createEntity();
        door.addTag(Tags::collisionable | Tags::door);
        EM.getCMPStorage().addRenderCMP(RenderCMP{"sprites/puerta.png"}, door);
        EM.getCMPStorage().addPositionCMP(PositionCMP{y,x,0,0}, door);
    }

    void clearMatrix(){
        for(int i = 0; i < 15; i++){
            for( int j=0; j<15; j++){
                actual_lvl[i][j] = 0; 
                random_lvl[i][j] = 0;
            }
        }
    }
};

