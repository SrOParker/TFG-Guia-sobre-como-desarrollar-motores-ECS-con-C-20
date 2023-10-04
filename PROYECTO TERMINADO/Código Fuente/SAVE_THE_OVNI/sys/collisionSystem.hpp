#include "../man/manentity.hpp"
#include "../map.hpp"
#include "../states.hpp"
struct CollisionSystem{
    void update(EntityManager& EM,Map& map, States& state);

    private:
    void collisionWithEnemy(EntityManager& EM, Map& map, States& state);
};
