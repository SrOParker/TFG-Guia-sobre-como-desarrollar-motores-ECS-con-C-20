#include "positionSys.hpp"


void PositionSys::update(EntityManager& EM){
    EM.forallMatching([&](Entity& e){
        auto& posCMP = EM.getCMPStorage().getPositionCMP(e);
        // para modificar la posicion necesitamos que otro sistema modifique stats,
        // en este caso los step, para sumarselos a la posicion
        // antes de esto hay que comprobar que no sobrepasen los límites del mapa
    }, maskToCheck);
}