#include "../man/manentity.hpp"
struct CollisionSystem{
    void update(EntityManager& EM, Texture2D& tex, float& speed);

    private:
    void collisionWithEnemy(EntityManager& EM, Texture2D& tex, float& speed);
};
