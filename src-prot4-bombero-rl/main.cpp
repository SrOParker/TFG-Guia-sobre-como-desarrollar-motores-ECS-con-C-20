#include <iostream>
#include <vector>
#include <raylib.h>
#include "game.hpp"

int main(){
    Game game;
    
    // Inicializar la ventana
    InitWindow(700, 400, "FIREFIGHTER GAME");

    // Bucle del juego
    game.run();
    
    
    // Cerrar la ventana y liberar los recursos
    CloseWindow();
   
    return 0;
}
