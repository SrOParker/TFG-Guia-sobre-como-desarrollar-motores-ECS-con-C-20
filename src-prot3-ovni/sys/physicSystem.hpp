#include "../man/manentity.hpp"

struct PhysicSystem{

    void update(EntityManager& EM);
    private:
    void checkPositions(EntityManager& EM, Entity& e);
};