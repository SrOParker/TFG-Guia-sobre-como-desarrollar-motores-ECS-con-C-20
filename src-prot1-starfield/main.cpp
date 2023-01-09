#include <iostream>
#include <vector>
#include <time.h>

//libreria uso de terminal de Francisco Gallego
#include "../libs/bltl/src/terminalhelper.hpp"
struct PhysicCMP{
    int x, y;
    int vx;
    PhysicCMP(){
        //srand(time(NULL));
        x = rand()%4;
        y = rand()%10; //entre 0 y 9
        vx = 1+ (rand()%5); //entre 1 y 4
    }
};

struct RenderCMP{
    char    sprite{};
    int     pos_to_draw{};
    
    RenderCMP(){
        pos_to_draw =0 ;
        sprite = '*';
    }
};

struct Entity{
    PhysicCMP phy{};
    RenderCMP rend{};     
};


struct EntityManagerP1
{
    using PointerToFunction = void(*)(Entity&);

    /// matrix   y -> 0 9    --    x -> 0 29
    EntityManagerP1(std::size_t size_for_entities = 10){
        entities.reserve(size_for_entities);
        for(int i=0; i<10; i++){
            map.emplace_back();
            for (int j=0; j<100; j++){
                map[i].push_back(' ');
            }
        }
    }
    
    auto& createEntity(){ return entities.emplace_back();}


    void forall(auto&& function){
        for(auto&e:entities){
            function(e);
        }
    }

    std::vector<Entity>& getEntityVector(){
        return entities;
    }
    std::vector<std::vector<char>>& getMap(){
        return map;
    }
    void clearMap(){
        for(int i=0; i<map.size(); i++){
            for (int j=0; j<map[0].size(); j++){
                map[i][j] = ' ';
            }
        }
    }
    private:    
    std::vector<Entity>  entities;
    std::vector<std::vector<char>> map;
};


struct PhysicsSystem{
    void update(EntityManagerP1& EM){
        EM.forall([&](Entity&e){
            e.phy.x += e.phy.vx;
            if(e.phy.x > 99){
                e.phy.x = 0;
                
            }
        });
    }
};
struct RenderSystem{
    void update(EntityManagerP1& EM){
    
        EM.forall([&](Entity&e){
            e.rend.pos_to_draw = e.phy.y;
            EM.getMap()[e.rend.pos_to_draw][e.phy.x] = e.rend.sprite;
            
        });
        

        draw(EM);
    }
    private:

    void draw(EntityManagerP1& EM){
        
        std::cout<< "--STARFIELD--\n ";
        std::cout<< "----------------------------------------------------------------------------------------------------\n";
        for(int i=0; i< EM.getMap().size(); i++){
            std::cout << "|";
            for (int j=0; j<EM.getMap()[0].size(); j++){
                std::cout<< EM.getMap()[i][j];
            }std::cout << "|\n";
        }
        std::cout<< "-----------------------------------------------------------------------------------------------------\n";
    }
};




struct Game {
    void run_game(EntityManagerP1 man){
        PhysicsSystem system_phy{};
        RenderSystem system_rend{};
        TERM::Terminal_t drawer{};
        bool running = true;
        int timer = 100;
        while(running){
            
            man.clearMap();
            
            if (timer == 0){
                system_phy.update(man);
                
                if(man.getEntityVector().size()<40){
                    man.createEntity();
                }

                timer = 100;
            } timer--;

            
            
            system_rend.update(man);
           
            pressKey(running, drawer);

            std::cout<< "\033[H\033[J";
           
        }
    }
    void pressKey(bool& running, TERM::Terminal_t& drawer){
        bool tecla = drawer.isKeyPressed();
        
        switch(tecla){
            case true: //escape
                //close game
                running = false;
                break;
            case false:
                break;
        }  
    }
};
int main(){
    EntityManagerP1 manager;
    Game game{};

    for (int i =0; i<10; i++){
        manager.createEntity();
    }
    game.run_game(manager);
    return 0;
}
