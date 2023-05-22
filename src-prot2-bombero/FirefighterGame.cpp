#include <iostream>
#include <vector>

//libreria uso de terminal de Francisco Gallego
#include "../libs/bltl/src/terminalhelper.hpp"

struct RenderComponent{
    const char* sprite{};
};
struct RoomComponent{
    int position{};
    int fire{};
};
struct MovementComponent{
    int yPos{};
};

struct Entity{
    bool has_render{};
    RenderComponent render{};
    
    bool has_room{};
    RoomComponent room{};
    
    bool has_movement{};
    MovementComponent movement{};
};



struct EntityManager{
    //using PointerToFunction = void(*)(Entity&);

    EntityManager(std::size_t size_for_entities = 10){
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

struct MovementSystem{
    void update(EntityManager& EM, bool& running, TERM::Terminal_t& drawer, int& score){
        EM.forall([&](Entity&e){
            if(e.has_movement == true){
                PressKey(EM, running, drawer, score);
            }
        });

    }
    private:
    void PressKey(EntityManager& EM, bool& running, TERM::Terminal_t& drawer, int& score){
        int tecla = drawer.wait4NextKeyPress();
        auto& player = EM.getEntityVector()[0];
        switch(tecla){
            
            case 119: // up w
                if(player.movement.yPos != 0){
                    player.movement.yPos -=1;
                    for(int i =0 ;i < 2; i++){
                        int roomRand = rand()%6;
                        EM.getEntityVector()[1+roomRand].room.fire += 1;
                        
                    }
                }
                break;
            case 115: // down s
                if(player.movement.yPos != 5){
                    player.movement.yPos +=1;
                    for(int i =0 ;i < 2; i++){
                        int roomRand = rand()%6;
                        EM.getEntityVector()[1+roomRand].room.fire += 1;
                    }
                }
                break;
            case 32:  // borrar fuego space
                score += EM.getEntityVector()[1+player.movement.yPos].room.fire;
                EM.getEntityVector()[1+player.movement.yPos].room.fire = 0;
                break;
            case 27: //close game ESC
                running = false;
                break;
        }
    }
};

struct RenderSystem{
    
    void update(EntityManager& EM, int score){
        //no hace falta el forall por que solo tenemos que pintar el mapa en este caso
        std::cout << "\033["<< TERM::AT_Bold <<";"<< TERM::FG_White <<"m------FIREFIGHTER GAME------ \033["<< TERM::BG_Default <<"m\n";
        
        //std::cout<<"SCORE: "<< score << "\n";
        auto& player = EM.getEntityVector()[0];
        for(int i=0; i < EM.getEntityVector().size() - 1 ; i++){
            if(player.movement.yPos==i){
                std::cout<< player.render.sprite;
            }else{
                std::cout<< " ";
            }
            std::cout<< "\033["<< TERM::AT_Bold <<";"<< TERM::FG_White <<"m|";
            int room_size =10;
            for(int j=0; j < EM.getEntityVector()[i+1].room.fire;j++){
                std::cout<< "\033["<< TERM::AT_Bold <<";"<< TERM::FG_Red <<"m"<< EM.getEntityVector()[i+1].render.sprite;
                room_size--;
            }
            for(int j=0; j<room_size;j++){
                std::cout<< " ";
            }
            room_size = 10;
            std::cout<< "\033["<< TERM::AT_Bold <<";"<< TERM::FG_White <<"m|\n";
        }
        std::cout<< "\033["<< TERM::AT_Bold <<";"<< TERM::FG_White <<"m----------------------------\n";
        std::cout << "\033["<< TERM::AT_Default <<";"<< TERM::FG_Magenta <<"mSCORE:" << score <<  "\n";
        std::cout <<"CONTROLS: W - UP | S - DOWN | SPACE - CLEAR  ROOM | ESC - CLOSE GAME \n";
    }
};






struct Game{

    void run(){
        MovementSystem movSys;
        RenderSystem rendSys;
        TERM::Terminal_t terminal_drawer{};
        int score=0;

        createEntitiesForFirefighterGame();
        bool running = true;
        
        while(running){
            if(checkRooms(running)){
                break;
            }
            
            rendSys.update(manager, score);
            movSys.update(manager, running, terminal_drawer, score);

            std::cout<< "\033[H\033[J"; 
        }
        
        rendSys.update(manager, score);
        std::cout<<"YOU LOSE, YOUR SCORE IS "<< score <<"\n"; 
    }

    private:

    void createEntitiesForFirefighterGame(){
        auto& player = manager.createEntity();
        player.render.sprite="B";
        player.has_render = true;
        player.has_movement = true;

        for(int i=0; i < 6; i++){
            auto& room_ENTITY = manager.createEntity();
            room_ENTITY.room.fire= rand()%3;
            room_ENTITY.room.position = i;
            room_ENTITY.render.sprite= "~";
            room_ENTITY.has_room = true;
            room_ENTITY.has_render = true;
        }

    }
    bool checkRooms(bool& running){
        for(int i =0 ; i<manager.getEntityVector().size()-1;i++){
            if(manager.getEntityVector()[i+1].room.fire > 9){
                running = false;   
                return true; 
            }
        }
        return false;

    }

    EntityManager manager;

};

int main(){
    
    Game game;
    
    game.run();
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