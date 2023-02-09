#include "../man/manentity.hpp"
struct RenderSystem{
    RenderSystem();
    void update(EntityManager& EM, float score);
    void printText(float score);
    private:
    int fontSize;
};