#include "../man/manentity.hpp"
struct CollisionSystem{
    void update(EntityManager& EM, Texture2D& tex, float& speed, bool& running);

    private:
    void collisionWithEnemy(EntityManager& EM, Texture2D& tex, float& speed, bool& running);
};
