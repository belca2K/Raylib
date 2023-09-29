#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screen_width = 1280;
    const int screen_height = 800;

    InitWindow(screen_width, screen_height, "raylib [text] example - sprite font loading");

    const char msg5[50] = "O player 1 venceu!";
    const char msg6[50] = "O player 2 venceu!";
    const char msg7[50] = "...Pressione [ENTER] para jogar novamente...";
    Vector2 fontPosition1 = { screen_width/2.0f - MeasureTextEx(font, msg5, (float)font.baseSize*2, -3).x/2,
                            screen_height/2-font.baseSize/2.0f};

    Vector2 fontPosition2 = { screen_width/2.0f - MeasureTextEx(font, msg7, (float)font.baseSize, -2.0f).x/2.0f,
                              screen_height/2.0f + font.baseSize/2.0f + 100.0f };

    Font font = LoadFont("C:\\raylib\\raylib\\examples\\text\\resources\\custom_alagard.png");        // Font loading

    
    Image radialGradient = GenImageGradientRadial(screen_width, screen_height, 0.0f, WHITE, MAROON);
    Texture2D texture = LoadTextureFromImage(radialGradient);
    UnloadImage(radialGradient);
    
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
            BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawTexture(texture1, 0, 0, WHITE);
            DrawTextEx(font, msg5, fontPosition5, (float)font.baseSize * 2, -3, WHITE);
            DrawTextEx(font, msg7, fontPosition7, (float)font.baseSize, -2, WHITE);

        EndDrawing();
    }
    UnloadTexture(texture);
    UnloadFont(font);      // Font unloading
    CloseWindow();          // Close window and OpenGL context
    
    return 0;
}