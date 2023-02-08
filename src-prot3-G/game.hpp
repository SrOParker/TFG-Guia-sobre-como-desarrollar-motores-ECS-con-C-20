#include "man/manentity.hpp"
#include "sys/physicSystem.hpp"
#include "sys/renderSystem.hpp"

struct Game{
    EntityManager EM{};
    PhysicSystem phy_sys{};
    RenderSystem rend_sys{};
    
    void crearEntidadesJuego(){
        auto& player = EM.createEntity();
        player.phy = PhysicCMP();
        player.rend= RenderCMP();
        

    }
    void run(){
        crearEntidadesJuego();
            // Definir la posición inicial de la textura
        float x = 0.0f;
        float y = 0.0f;

        // Velocidad de la imagen
        float speed = 2.0f;
        Texture2D background = LoadTexture("img/background.png");

        SetTargetFPS(60);
        while (!WindowShouldClose()){
            // Limpiar la pantalla con un color rojo
            x -= speed;
            if (x <= -background.width) x = 0;
            // Dibujar la ventana
            BeginDrawing();
                ClearBackground(RAYWHITE);
                

                DrawTextureEx(background, Vector2{x,y}, 0.0f, 1.0f, WHITE);
                DrawTextureEx(background, Vector2{x + background.width, y}, 0.0f, 1.0f, WHITE);

                // Actualizar la posición de la textura
                

                
                phy_sys.update(EM);
                rend_sys.update(EM);
            EndDrawing();
            

        }
        UnloadTexture(background);
    }
    
};