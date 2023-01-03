#include <iostream>
#include <vector>

//libreria uso de terminal de Francisco Gallego
#include "../libs/bltl/src/terminalhelper.hpp"

struct Cmp_Physics{
    float y{};
    float vy{};
};

struct Cmp_Render{
    char c{};
    int pos_to_draw{};
};

struct Entity{
    Cmp_Physics physics;
    Cmp_Render render;
};


template <typename Type>
struct EntityManager{
    using PointerToFunction = void(*)(Type&);

    EntityManager(std::size_t size_for_entities = 10){
        entities.reserve(size_for_entities);
    }
    
    auto& createEntity(){ return entities.emplace_back();}


    void forall(PointerToFunction function){
        for(auto&e:entities){
            function(e);
        }
    }
    private:    
    std::vector<Type>  entities;
};

struct PhysicsSystem{
    void update(EntityManager<Entity>& EM){
        EM.forall(update_one_entity);
    }
    
    private:
    static void update_one_entity(Entity& e){
        e.physics.y += e.physics.vy;
    }

};
struct RenderSystem{
    
    void update(EntityManager<Entity>& EM, Entity& player){
        
        EM.forall([](Entity&e){
            e.render.pos_to_draw = e.physics.y;
        });

        drawMap(player);
    }

    private:
    void drawMap(Entity& player){
        std::cout << "\033["<< TERM::AT_Bold <<";"<< TERM::FG_Red <<"m---------B GAME---------\033["<< TERM::BG_White <<"m\n";
        //std::cout << "\033["<< TERM::AT_Bold <<";"<< TERM::FG_Red <<"mbold red text\n";
        int size_of_building = 4;
        int size_of_rooms=10;
        for(int i=0; i < size_of_building;i++){
            if(i == player.physics.y){
                //std::cout<< player.render.c;
                std::cout << "\033["<< TERM::AT_Bold <<";"<< TERM::FG_Green <<"m"<< player.render.c;
            }else{
                std::cout<< " ";
            }
            //std::cout<< "|";
            std::cout << "\033["<< TERM::AT_Bold <<";"<< TERM::FG_Blue <<"m|";
            for (int j = 0; j < size_of_rooms;j++){
                std::cout<< " ";
            }
            std::cout << "\033["<< TERM::AT_Bold <<";"<< TERM::FG_Blue <<"m|\n";
        }
    }

    
};



void PressKey(Entity& player, bool& running, TERM::Terminal_t& drawer){
    int tecla = drawer.wait4NextKeyPress();
    
    switch(tecla){
        case 119: // up
            if (player.physics.y>0){
                player.physics.vy = -1;
            }else{
                player.physics.vy = 0;
            }
            break;
        case 115: // down
            if (player.physics.y<3){
                player.physics.vy = 1;
            }else{
                player.physics.vy = 0;
            }
            break;
        case 13:
            //borrar fuego
            break;
    }


}

void game(EntityManager<Entity>& manager){
    PhysicsSystem phySys;
    RenderSystem rendSys;
    TERM::Terminal_t terminal_drawer{};

    auto& player = manager.createEntity();
    player.render.c='B';

    bool running = true;
    
    while(running){

        phySys.update(manager);
        rendSys.update(manager, player);
        
        PressKey(player, running, terminal_drawer);
        

        std::cout<< "\033[H\033[J"; 
        //terminal_drawer.clearBuffer();

    }
}



int main(){
    EntityManager<Entity> manager;
    
    game(manager);
    return 0;
}


//  POINTS : 10
//  |~            |
//  |~~~~~        | 
//  |~            |
//  |             |
//  |             |
// B|             |
//  |             |
//  |             |