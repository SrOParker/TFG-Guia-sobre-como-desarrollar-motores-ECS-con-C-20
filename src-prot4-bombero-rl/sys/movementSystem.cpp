#include "movementSystem.hpp"

void MovementSystem::update(EntityManager& EM, bool& running, int& score){
    EM.forall([&](Entity&e){
        if(e.has_movement == true){
            PressKey(EM, e, running, score);
        }
    });
}
void MovementSystem::PressKey(EntityManager& EM, Entity& e, bool& running, int& score){
    if(e.has_movement){
        if (IsKeyDown(KEY_W)){
            if(e.movement.yPos != 0){
                e.movement.yPos -=1;
                for(int i =0 ;i < 2; i++){
                    int roomRand = rand()%6;
                    EM.getEntityVector()[1+roomRand].room.fire += 1;
                }
            }
        }
        if (IsKeyDown(KEY_S)){
            if(e.movement.yPos != 5){
                e.movement.yPos +=1;
                for(int i =0 ;i < 2; i++){
                    int roomRand = rand()%6;
                    EM.getEntityVector()[1+roomRand].room.fire += 1;
                }
            }
        }
        if (IsKeyDown(KEY_SPACE)){
            score += EM.getEntityVector()[1+e.movement.yPos].room.fire;
            EM.getEntityVector()[1+e.movement.yPos].room.fire = 0;
            
        }
        if (IsKeyDown(KEY_ESCAPE)){
            running = false;
        }
    }
}