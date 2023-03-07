#include "../man/manentity.hpp"
struct RenderSystem{
    RenderSystem();
    void update(EntityManager& EM, float score);
    void printScore(float score);
    void printRecord(float record);
    void printExit();
    void printDifficultySelected(int dif);
    private:
    int fontSize;
};