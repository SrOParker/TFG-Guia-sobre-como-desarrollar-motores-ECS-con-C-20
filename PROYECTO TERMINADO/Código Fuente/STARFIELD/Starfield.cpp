#include <iostream>
#include <vector>
#include <time.h>

//libreria uso de terminal de Francisco Gallego
#include "../libs/bltl/src/terminalhelper.hpp"


struct PhysicCMP{
    int x, y;
    int vx;
    PhysicCMP(){
        x = rand()%4;       //entre 0 y 3
        y = rand()%10;      //entre 0 y 9
        vx = 1+ (rand()%5); //entre 1 y 4
    }
};

struct RenderCMP{
    char    sprite{'*'};
};

struct Entity{
    PhysicCMP phy{};
    RenderCMP rend{};     
};


struct EntityManagerP1
{
    using PointerToFunction = void(*)(Entity&);

    /// matrix   y -> 0 9    --    x -> 0 99
    EntityManagerP1(std::size_t size_for_entities = 10){
        entities.reserve(size_for_entities);
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

    private:    
    std::vector<Entity>  entities;
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
            std::cout <<"\033["<< e.phy.y <<";"<< e.phy.x<<"f" ;
            std::cout << "\033["<< TERM::AT_Bold <<";"
                      << TERM::FG_Cyan <<"m";
            std::cout << e.rend.sprite;
        });
    }
};




struct Game {
    EntityManagerP1 manager;

    void run_game(){
        PhysicsSystem system_phy{};
        RenderSystem system_rend{};
        TERM::Terminal_t drawer{};
        bool running = true;
        int timer = 100;
        while(running){
            system_rend.update(manager);
            if(timer == 0){
                system_phy.update(manager);
                timer = 100;
                            
                if(manager.getEntityVector().size()<40){
                    manager.createEntity();
                }
            }else{
                timer--;
            }

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
    Game game{};
    game.run_game();
    return 0;
}
