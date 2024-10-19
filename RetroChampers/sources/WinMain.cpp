#include "Precompiled.h"
#include "raylib.h"

//---[ Display & Mouse ]---
static const int screenWidth = 1280;
static const int screenHeight = 720;
static Vector2 mousePosition = { 0.0f, 0.0f };

int main(void)
{
    // INITIALIZATION
    //---[ Window ]---
    InitWindow(screenWidth, screenHeight, "RetroChamper_v0.1_Demo");
    SetTargetFPS(60);
    SetExitKey(0);

    //---[ Font ]---
    Font gameFont = LoadFont("resources/fonts/alagard.png");

    //---[ Textures ]---

    //---[ Singleton ]---

    //---[ Scene ]---

    //---[ Time ]---

    //---[ UI ]---

    //---[ Player ]---

    //---[ Inventory ]---

    //---[ Item ]---

    //---[ Enemy ]---


    //--------------------------------------------------------------------------------------
    // MAIN GAME LOOP
    while (WindowShouldClose() == false)
    {
        // UPDATE
        

        //----------------------------------------------------------------------------------
        // DRAW
        BeginDrawing();
        ClearBackground(BLACK);

        // ---[ Draw Active Scene ]---



        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // DE-INITIALIZATION



    //---[ Font ]---
    UnloadFont(gameFont);

    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}