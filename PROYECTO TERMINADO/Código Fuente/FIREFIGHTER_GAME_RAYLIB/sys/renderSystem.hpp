#pragma once
#include "../man/manentity.hpp"
#include "../map.hpp"
//#include <iomanip>
#include <sstream>
#include <iostream>
#define COL_NUMBER 13
#define ROW_NUMBER 7
//Cada columna  700/13 = 53'84
//Cada fila     400/7  = 57,14   

struct RenderSystem{
    RenderSystem();
    void update(EntityManager& EM, Map& map, int score);
    void printLose();
    
    private:
    void printText(int& score);
   
    float row_size{}, col_size{};
};

