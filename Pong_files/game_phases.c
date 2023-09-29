#include "raylib.h"
#include <stdlib.h>

typedef struct
{
    float x,y;
    int speed_x, speed_y; //speed_x was a mistake, but I will let it be in case I change my mind
    float radius;
    int score_player1, score_player2;
}Ball;
typedef struct
{
    float x, y;
    float width, height;
    int speed_x, speed_y;
}Paddle;
enum paddles {
    player1, player2
}; //left and right
enum game_phases{
    menu, gameplay_choice, game_pvp, game_pve , win_screen, lose_screen
};

void ballUpdate(Ball *ball);
void player1Update(Paddle *paddle);
void player2Update(Paddle *paddle);
void cpuUpdate(Paddle *paddle, Ball ball);
void resetBall(Ball *ball);

int main ()
{
    const int screen_width=1280;
    const int screen_height=800;

    Color Green = {38, 185, 154,255};
    Color Dark_Green = {20, 160, 133,255};
    Color Light_Green = {129, 204, 184,255};
    Color Yellow = {243, 213, 91,255};

    Ball ball;
    ball.x = screen_width/2;
    ball.y = screen_height/2;
    ball.speed_x = 7;
    ball.speed_y = 7;
    ball.radius = 20;
    ball.score_player1=0;
    ball.score_player2=0;
//initialize left player
    Paddle paddle[2];
    paddle[player1].x=10;
    paddle[player1].y=screen_height/2 - 60;
    paddle[player1].width=25;
    paddle[player1].height= 120;
    paddle[player1].speed_x=2;
    paddle[player1].speed_y=6;
//initialize right player
    paddle[player2].x=screen_width - 35;
    paddle[player2].y=screen_height/2 - 60;
    paddle[player2].width=25;
    paddle[player2].height=120;
    paddle[player2].speed_x=2;
    paddle[player2].speed_y=6;
//game phases
    int game_phase=0;
    InitWindow(screen_width, screen_height, "Pongpong");
//menu things
    const char msg1[50] = "MENU";
    const char msg2[50] = "...Pressione [ENTER] para jogar...";

    Font font = LoadFont("C:\\raylib\\raylib\\examples\\text\\resources\\custom_alagard.png");        // Font loading

    Vector2 fontPosition1 = { screen_width/2.0f - MeasureTextEx(font, msg1, (float)font.baseSize * 3, -3).x/2,
                            font.baseSize/2.0f + 150.0f };

    Vector2 fontPosition2 = { screen_width/2.0f - MeasureTextEx(font, msg2, (float)font.baseSize, -2.0f).x/2.0f,
                              screen_height/2.0f - font.baseSize/2.0f - 10.0f };
    
    Image radialGradient = GenImageGradientRadial(screen_width, screen_height, 0.0f, WHITE, BLACK);
    Texture2D texture = LoadTextureFromImage(radialGradient);
    UnloadImage(radialGradient);
//------------------------------------
    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        BeginDrawing();
            
        if(game_phase == menu)
        {
            ClearBackground(RAYWHITE);
            DrawTexture(texture, 0, 0, WHITE);
            DrawTextEx(font, msg1, fontPosition1, (float)font.baseSize * 3, -3, WHITE);
            DrawTextEx(font, msg2, fontPosition2, (float)font.baseSize, -2, WHITE);
            if(IsKeyPressed(KEY_ENTER)) game_phase++;
        }
        else if(game_phase == game_pvp)
        {   //atualizar as posições
            ballUpdate(&ball);
            player1Update(&paddle[player1]);
            player2Update(&paddle[player2]);
            if(CheckCollisionCircleRec((Vector2){ball.x, ball.y}, ball.radius,(Rectangle){paddle[player1].x, paddle[player1].y, paddle[player1].width, paddle[player1].height}))
            {
                ball.speed_x *= -1;
            }
            if(CheckCollisionCircleRec((Vector2){ball.x, ball.y}, ball.radius,(Rectangle){paddle[player2].x, paddle[player2].y, paddle[player2].width, paddle[player2].height}))
            {
                ball.speed_x *= -1;
            }
            ClearBackground(Dark_Green);
            DrawRectangle(screen_width/2, 0, screen_width/2, screen_height, Green);
            DrawCircle(screen_width/2, screen_height/2, 150, Light_Green);
            DrawLine(screen_width/2, 0, screen_width/2, screen_height, WHITE);
            DrawRectangleRounded((Rectangle){paddle[player1].x, paddle[player1].y, paddle[player1].width, paddle[player1].height}, 1, 0, WHITE);
            DrawRectangleRounded((Rectangle){paddle[player2].x, paddle[player2].y, paddle[player2].width, paddle[player2].height}, 1, 0, WHITE);
            DrawCircle(ball.x, ball.y, ball.radius, Yellow);
            DrawText(TextFormat("%i", ball.score_player1), screen_width/4 -20, 20, 80, WHITE);
            DrawText(TextFormat("%i", ball.score_player2), 3*screen_width/4 -20, 20, 80, WHITE);
        }
        else if(game_phase == game_pve){
            ballUpdate(&ball);
            player1Update(&paddle[player1]);
            cpuUpdate(&paddle[player2], ball);
            if(CheckCollisionCircleRec((Vector2){ball.x, ball.y}, ball.radius,(Rectangle){paddle[player1].x, paddle[player1].y, paddle[player1].width, paddle[player1].height}))
            {
                ball.speed_x *= -1.15;
                paddle[player1].speed_y += 0.5;
            }
            if(CheckCollisionCircleRec((Vector2){ball.x, ball.y}, ball.radius,(Rectangle){paddle[player2].x, paddle[player2].y, paddle[player2].width, paddle[player2].height}))
            {
                ball.speed_x *= -1;
            }
            ClearBackground(Dark_Green);
            DrawRectangle(screen_width/2, 0, screen_width/2, screen_height, Green);
            DrawCircle(screen_width/2, screen_height/2, 150, Light_Green);
            DrawLine(screen_width/2, 0, screen_width/2, screen_height, WHITE);
            DrawRectangleRounded((Rectangle){paddle[player1].x, paddle[player1].y, paddle[player1].width, paddle[player1].height}, 1, 0, WHITE);
            DrawRectangleRounded((Rectangle){paddle[player2].x, paddle[player2].y, paddle[player2].width, paddle[player2].height}, 1, 0, WHITE);
            DrawCircle(ball.x, ball.y, ball.radius, Yellow);
            DrawText(TextFormat("%i", ball.score_player1), screen_width/4 -20, 20, 80, WHITE);
            DrawText(TextFormat("%i", ball.score_player2), 3*screen_width/4 -20, 20, 80, WHITE);
        }
        EndDrawing();
    }

    UnloadTexture(texture);
    UnloadFont(font);// Font unloading

    CloseWindow();
    return 0;
}

void ballUpdate(Ball *ball)
{
    ball->x += ball->speed_x;
    ball->y += ball->speed_y;
    
    if(ball->y + ball->radius >= GetScreenHeight() || ball->y - ball->radius <= 0)
    {
        ball->speed_y *= -1;
    }
    if(ball->x + ball->radius >=GetScreenWidth())
    {
        ball->score_player1++;
        resetBall(ball);
    }
    if(ball->x - ball->radius <=0)
    {
        ball->score_player2++;
        resetBall(ball);
    }
}
void resetBall(Ball *ball)
{
    ball->y = GetScreenHeight()/2;
    ball->x = GetScreenWidth()/2;

    int speed_choices[2] = {-1, 1};
    ball->speed_x *= speed_choices[GetRandomValue(0,1)];
    ball->speed_y *= speed_choices[GetRandomValue(0,1)];
}

void player1Update(Paddle *paddle)
{   //mexer na vertical
    if(IsKeyDown(KEY_W))    paddle->y -= paddle->speed_y;
    if(IsKeyDown(KEY_S))    paddle->y += paddle->speed_y;
    if(paddle->y + paddle->height >= GetScreenHeight())paddle->y = GetScreenHeight() - paddle->height;
    if(paddle->y <= 0) paddle->y = 0;
}
void player2Update(Paddle *paddle)
{   //mexer na vertical
    if(IsKeyDown(KEY_UP))    paddle->y -= paddle->speed_y;
    if(IsKeyDown(KEY_DOWN))    paddle->y += paddle->speed_y;
    if(paddle->y + paddle->height >= GetScreenHeight())paddle->y = GetScreenHeight() - paddle->height;
    if(paddle->y <= 0) paddle->y = 0;

}
void cpuUpdate(Paddle *paddle, Ball ball) //mini IA  pra jogar contra a maquina
{
    if(paddle->y+ paddle->height/2 > ball.y) paddle->y -= paddle->speed_y;
    else paddle->y += paddle->speed_y;
    
    if(paddle->y + paddle->height >= GetScreenHeight())paddle->y = GetScreenHeight() - paddle->height;
    if(paddle->y <= 0) paddle->y = 0;
}