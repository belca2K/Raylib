#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [audio] example - music playing (streaming)");

    InitAudioDevice();

    Music gameplay = LoadMusicStream("C:\\Users\\bruno\\Desktop\\Pong\\Pong_files\\resources\\gameplay.mp3");
    Music menu = LoadMusicStream("C:\\Users\\bruno\\Desktop\\Pong\\Pong_files\\resources\\menu.mp3");
    PlayMusicStream(gameplay);
    PlayMusicStream(menu);
    SetMusicVolume(gameplay, 0.15f);
    SetMusicVolume(menu, 0.6f);
    //mexi so ate aq
    bool x = true;
    SetTargetFPS(60);
    while (!WindowShouldClose()) 
    {   
        if(IsKeyPressed(KEY_ENTER)) x = !x;

        if (x==false)
        {
            StopMusicStream(menu);
            PlayMusicStream(gameplay);
            UpdateMusicStream(gameplay); 
        }
        else if(x==true)
        {
            StopMusicStream(gameplay);
            PlayMusicStream(menu);
            UpdateMusicStream(menu);
        }
        
        EndDrawing();
    }
    UnloadMusicStream(gameplay);
    UnloadMusicStream(menu);
    CloseAudioDevice();
    
    CloseWindow();
    return 0;
}