#include "collisionSys.hpp"


void CollisionSystem::update(EntityManager& EM, GameManager& GM, bool& playing_lvl, States& state, int& lvlActual){
    EM.forallMatching([&](Entity& e){
        auto& posCMPOfCollider = EM.getCMPStorage().getPositionCMP(e);
        if(posCMPOfCollider.velX!=0 || posCMPOfCollider.velY!=0){
            EM.forallMatching([&](Entity& coll){
                auto& posCMPOfCollisionable = EM.getCMPStorage().getPositionCMP(coll);
                if(checkCollision(posCMPOfCollider, posCMPOfCollisionable)){
                    if(coll.hasTag(Tags::wall)){
                        collisionWithWall(EM, GM, e, coll, posCMPOfCollider);
                    }else if(!e.hasTag(Tags::enemy) && coll.hasTag(Tags::enemy)){
                        collisionWithEnemy(EM, GM, e, coll);
                    }else if(e.hasTag(Tags::enemy) && coll.hasTag(Tags::player)){
                        collisionWithPlayer(EM, coll, e, state, playing_lvl);
                    }else if(e.hasTag(Tags::player) && coll.hasTag(Tags::chest) && !coll.hasTag(Tags::object_picked)){
                        collisionWithChest(EM, GM, e, coll);
                    }else if(e.hasTag(Tags::player) && coll.hasTag(Tags::key)){
                        collisionWithKey(EM, GM, e, coll);
                    }else if(e.hasTag(Tags::player | Tags::has_key) && coll.hasTag(Tags::door)){
                        collisionWithDoor(playing_lvl, lvlActual);
                    }
                }


            }, cmpMaskToCheck, Tags::collisionable);
        }
    },cmpMaskToCheck, tagMaskToCheck);
}

void CollisionSystem::collisionWithWall(EntityManager& EM, GameManager& GM, Entity& ent, Entity& wall, PositionCMP& collider){
    //Check Collision
    collider.velX = 0;
    collider.velY = 0;

    if(ent.hasTag(Tags::player)){    // Hit Wall
        auto& statsPlayer = EM.getCMPStorage().getStatsCMP(ent);
        auto& statsWall = EM.getCMPStorage().getStatsCMP(wall);
        auto& rendWall = EM.getCMPStorage().getRenderCMP(wall);
        auto& posWall = EM.getCMPStorage().getPositionCMP(wall);
        statsWall.health -= statsPlayer.pickaxe;
        rendWall.actual_frame++;
        rendWall.frame = {(float)(rendWall.actual_frame*32), 0,(float)32, (float)rendWall.sprite.height};
        if(statsWall.health <= 0){
            //Eliminar Entidad
            GM.getActualMap()[posWall.posY][posWall.posX] = 0;
            EM.removeEntity(wall);
        }
    }
}

void CollisionSystem::collisionWithEnemy(EntityManager& EM,GameManager& GM, Entity& player, Entity& enemy){
    auto& player_stats  = EM.getCMPStorage().getStatsCMP(player);
    auto& player_pos    = EM.getCMPStorage().getPositionCMP(player);
    auto& enemy_stats   = EM.getCMPStorage().getStatsCMP(enemy);
    auto& enemy_pos     = EM.getCMPStorage().getPositionCMP(enemy);
    player_pos.velX = 0;
    player_pos.velY = 0;
    if(rand() % 100 <= player_stats.critical_hit){
        enemy_stats.health = enemy_stats.health - player_stats.damage*2;
    }else{
        enemy_stats.health = enemy_stats.health - player_stats.damage;
    }

    if (enemy_stats.health <= 0){
        GM.getActualMap()[enemy_pos.posY][enemy_pos.posX] = 0;
        EM.removeEntity(enemy);
    }

}

bool CollisionSystem::checkCollision(PositionCMP& pos1, PositionCMP& pos2){
    bool removedHorizontal = false;
    bool removedVertical = false;
    int directionX=0;
    if(pos1.velX<0){ directionX= -1; }else{ directionX = 1; }
    int directionY=0;
    if(pos1.velY<0){ directionY= -1; }else{ directionY = 1; }
            
    if((pos1.velX != 0) && 
        (pos2.posY == pos1.posY && 
        ((pos1.posX + directionX) == pos2.posX))){
        //Try moving HORIZONTAL (Key A OR D)
        removedHorizontal = true;
        pos1.velX = 0;
    }
    
    if((pos1.velY != 0) && 
        (pos2.posX == pos1.posX && 
        ((pos1.posY + directionY) == pos2.posY))){
        //Try moving VERTICAL (Key W OR S)
        removedVertical = true;
        pos1.velY = 0;
    }
    if(removedHorizontal || removedVertical){
        return true;
    }
    return false;
}

void CollisionSystem::collisionWithPlayer(EntityManager& EM, Entity& player, Entity& enemy, States& state, bool& playing_lvl){
    auto& player_stats  = EM.getCMPStorage().getStatsCMP(player);
    auto& enemy_pos     = EM.getCMPStorage().getPositionCMP(enemy);
    auto& enemy_stats   = EM.getCMPStorage().getStatsCMP(enemy);
    
    player_stats.health -= enemy_stats.damage;
    enemy_pos.velX = 0;
    enemy_pos.velY = 0;

    if(player_stats.health <= 0){
        //Morimos
        std::cout<< "Has muerto\n";
        state = States::MENU;
        playing_lvl = false;
    }

}

void CollisionSystem::collisionWithChest(EntityManager& EM, GameManager& GM, Entity& player, Entity& chest){
    //COLISIONAMOS CON EL OBJETO
    auto& posPlayer = EM.getCMPStorage().getPositionCMP(player);
    posPlayer.velX = 0;
    posPlayer.velY = 0;
    //GENERAR OBJ ALEATORIAMENTE
    auto& obj = GM.createObject(EM, rand()%5);
    //APLICAR SUS ESTADISTICAS AL PLAYER
    auto& statsPlayer = EM.getCMPStorage().getStatsCMP(player);
    auto& statsObj    = EM.getCMPStorage().getStatsCMP(obj);
    statsPlayer.health+=statsObj.health;
    statsPlayer.maxhealth+=statsObj.maxhealth;
    statsPlayer.damage += statsObj.damage;
    statsPlayer.step += statsObj.step;
    statsPlayer.critical_hit += statsObj.critical_hit;
    statsPlayer.pickaxe += statsObj.pickaxe;
    //CAMBIAR SPRITE DEL COFRE Y HACERLO INACCESIBLE
    auto& rendChest = EM.getCMPStorage().getRenderCMP(chest);
    rendChest.actual_frame++;
    rendChest.frame = {(float)(rendChest.actual_frame*32), 0,(float)32, (float)rendChest.sprite.height};
    chest.addTag(Tags::object_picked);
}

void CollisionSystem::collisionWithKey(EntityManager& EM, GameManager& GM, Entity& player, Entity& key){
    auto& posKey = EM.getCMPStorage().getPositionCMP(key);
    GM.getActualMap()[posKey.posY][posKey.posX] = 0;
    posKey.posX =  16;
    posKey.posY =   0;
    player.addTag(Tags::has_key);
}

void CollisionSystem::collisionWithDoor(bool& playing_lvl, int& lvlActual){
    //go to other lvl
    std::cout<< "Charging lvl2"<<"\n";
    lvlActual++;
    playing_lvl = false;
}