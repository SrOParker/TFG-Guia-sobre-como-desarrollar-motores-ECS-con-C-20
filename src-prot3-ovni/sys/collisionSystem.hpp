#include "../man/manentity.hpp"
#include "../map.hpp"
struct CollisionSystem{
    void update(EntityManager& EM,Map& map, bool& running);

    private:
    void collisionWithEnemy(EntityManager& EM, Map& map, bool& running);
};
