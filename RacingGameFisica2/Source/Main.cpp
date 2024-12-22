#include "Application.h"
#include "Globals.h"
#include "ModuleRender.h"
#include "raylib.h"

#include <stdlib.h>

enum main_states
{
    MAIN_CREATION,
    MAIN_START,
    MAIN_UPDATE,
    MAIN_FINISH,
    MAIN_EXIT,
    MAIN_SCREEN1,
    MAIN_SCREEN2
};

Texture2D screen1Image;
Texture2D screen2Image;

void DrawScreen1()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(screen1Image, 940,860, WHITE);
    DrawText("Pantalla 1: Presiona SPACE para continuar", 190, 200, 20, RED);
    EndDrawing();
}

void DrawScreen2()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(screen2Image, 880, 840, WHITE);
    DrawText("Pantalla 2: Presiona T para continuar", 190, 200, 20, RED);
    EndDrawing();
}

int main(int argc, char** argv)
{
    LOG("Starting game '%s'...", TITLE);

    int main_return = EXIT_FAILURE;
    main_states state = MAIN_CREATION;
    Application* App = NULL;

    InitWindow(800, 600, TITLE); // Inicializar la ventana

    // Cargar las imágenes
    screen1Image = LoadTexture("Assets/mainScreen.png");
    if (screen1Image.id == 0)
    {
        LOG("Error al cargar la imagen Assets/crate.png");
    }
    else
    {
        LOG("Imagen Assets/crate.png cargada correctamente");
    }

    screen2Image = LoadTexture("Assets/holaScreen.png");
    if (screen2Image.id == 0)
    {
        LOG("Error al cargar la imagen Assets/holaScreen.png");
    }
    else
    {
        LOG("Imagen Assets/holaScreen.png cargada correctamente");
    }

    while (state != MAIN_EXIT && !WindowShouldClose())
    {
        switch (state)
        {
        case MAIN_CREATION:

            LOG("-------------- Application Creation --------------");
            App = new Application();
            state = MAIN_START;
            break;

        case MAIN_START:

            LOG("-------------- Application Init --------------");
            if (App->Init() == false)
            {
                LOG("Application Init exits with ERROR");
                state = MAIN_EXIT;
            }
            else
            {
                state = MAIN_SCREEN1;
                LOG("-------------- Application Screen 1 --------------");
            }

            break;

        case MAIN_SCREEN1:
            DrawScreen1();
            if (IsKeyPressed(KEY_SPACE))
            {
                state = MAIN_SCREEN2;
                LOG("-------------- Application Screen 2 --------------");
            }
            break;

        case MAIN_SCREEN2:
            DrawScreen2();
            if (IsKeyPressed(KEY_T))
            {
                state = MAIN_UPDATE;
                LOG("-------------- Application Update --------------");
            }
            break;

        case MAIN_UPDATE:
        {
            int update_return = App->Update();

            if (update_return == UPDATE_ERROR)
            {
                LOG("Application Update exits with ERROR");
                state = MAIN_EXIT;
            }

            if (update_return == UPDATE_STOP)
                state = MAIN_FINISH;
        }
        break;

        case MAIN_FINISH:

            LOG("-------------- Application CleanUp --------------");
            if (App->CleanUp() == false)
            {
                LOG("Application CleanUp exits with ERROR");
            }
            else
                main_return = EXIT_SUCCESS;

            state = MAIN_EXIT;

            break;

        }
    }

    // Descargar las imágenes
    UnloadTexture(screen1Image);
    UnloadTexture(screen2Image);

    delete App;
    CloseWindow(); // Cerrar la ventana
    LOG("Exiting game '%s'...\n", TITLE);
    return main_return;
}