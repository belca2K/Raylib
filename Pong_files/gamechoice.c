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


    Font font = LoadFont("C:\\raylib\\raylib\\examples\\text\\resources\\custom_alagard.png");        // Font loading

    const char msg3[50] = "       Pressione [1]\npara jogar singleplayer...";
    const char msg4[50] = "       Pressione [2]\npara jogar multiplayer...";
    Vector2 fontPosition3 = { screen_width/4.0f - MeasureTextEx(font, msg3, (float)font.baseSize, -3).x/2,
                            screen_height/2.0f - font.baseSize/2.0f};

    Vector2 fontPosition4 = { screen_width/1.33f - MeasureTextEx(font, msg4, (float)font.baseSize, -2.0f).x/2.0f,
                              screen_height/2.0f - font.baseSize/2.0f};
    
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
            BeginDrawing();

            ClearBackground(SKYBLUE);
            DrawRectangle(screen_width/2, 0, screen_width/2, screen_height, MAROON);
            DrawTextEx(font, msg3, fontPosition3, (float)font.baseSize, -3, WHITE);
            DrawTextEx(font, msg4, fontPosition4, (float)font.baseSize, -2, WHITE);

        EndDrawing();
    }
    UnloadFont(font);      // Font unloading
    CloseWindow();          // Close window and OpenGL context
    
    return 0;
}