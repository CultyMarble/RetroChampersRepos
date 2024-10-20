#include "Precompiled.h"
#include "raylib.h"

#include "TilemapSystem.h"

using namespace tms;

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
    Texture2D tileAtlas = LoadTexture("resources/link_master_atlas.png");

    //---[ Singleton ]---
    TilemapSystem::StaticInitialize();

    //---[ Scene ]---
    TilemapSystem::Get()->LoadMaps("resources/maps");
    TilemapSystem::Get()->SetActiveMap(0);

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
        auto* activeMapData = TilemapSystem::Get()->GetActiveMapData();
        for (const auto& tile : *activeMapData)
        {
            Rectangle srcRect = { tile.textureIDx * 64.0f, tile.textureIDy * 64.0f, 64.0f, 64.0f };
            Rectangle destRect = tile.collisionBox;

            // Draw the tile from the atlas
            DrawTexturePro(tileAtlas, srcRect, destRect, Vector2{ 0, 0 }, 0.0f, WHITE);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // DE-INITIALIZATION
    //---[ Singleton ]---
    tms::TilemapSystem::StaticTerminate();

    //---[ Texture ]---
    UnloadTexture(tileAtlas);

    //---[ Font ]---
    UnloadFont(gameFont);

    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}