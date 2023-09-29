#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib [text] example - sprite font loading");

    const char msg1[50] = "MENU";
    const char msg2[50] = "...Pressione [ENTER] para jogar...";
    const char msg3[50] = "...and a THIRD one! GREAT! :D";

    Font font = LoadFont("C:\\raylib\\raylib\\examples\\text\\resources\\custom_alagard.png");        // Font loading

    Vector2 fontPosition1 = { screenWidth/2.0f - MeasureTextEx(font, msg1, (float)font.baseSize * 3, -3).x/2,
                            font.baseSize/2.0f + 80.0f };

    Vector2 fontPosition2 = { screenWidth/2.0f - MeasureTextEx(font, msg2, (float)font.baseSize, -2.0f).x/2.0f,
                              screenHeight/2.0f - font.baseSize/2.0f - 10.0f };

    Vector2 fontPosition3 = { screenWidth/2.0f - MeasureTextEx(font, msg3, (float)font.baseSize, 2.0f).x/2.0f,
                              screenHeight/2.0f - font.baseSize/2.0f + 50.0f };

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
            BeginDrawing();

            ClearBackground(RAYWHITE);

            //DrawTextEx(Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint); 
            DrawTextEx(font, msg1, fontPosition1, (float)font.baseSize * 3, -3, WHITE);
            DrawTextEx(font, msg2, fontPosition2, (float)font.baseSize, -2, WHITE);

        EndDrawing();
    }
    UnloadFont(font);      // Font unloading
    CloseWindow();          // Close window and OpenGL context
    return 0;
}