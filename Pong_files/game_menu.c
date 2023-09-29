#include "raylib.h"
#include <stdlib.h>

int main()
{
    const int screen_width=1280;
    const int screen_height=800;

    InitWindow(screen_width, screen_height, "Pongpong");
    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        BeginDrawing();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}