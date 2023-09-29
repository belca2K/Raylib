#include "raylib.h"
#include <stdlib.h>

typedef struct
{
    float x,y;
    int speed_x, speed_y;
    float radius;
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

void ballUpdate(Ball *ball);
void player1Update(Paddle *paddle);
void player2Update(Paddle *paddle);
void cpuUpdate(Paddle *paddle, Ball ball);

int main ()
{
    const int screen_width=1280;
    const int screen_height=800;

    Ball ball;
    ball.x = screen_width/2;
    ball.y = screen_height/2;
    ball.speed_x = 7;
    ball.speed_y = 7;
    ball.radius = 20;
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

    InitWindow(screen_width, screen_height, "Pongpong");
    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        BeginDrawing();
        //atualizar as posições
        ballUpdate(&ball);
        player1Update(&paddle[player1]);
        //decidir no case do jogo qual vai ser o player2
        player2Update(&paddle[player2]);
        cpuUpdate(&paddle[player2], ball);
        //checar colisoes
        if(CheckCollisionCircleRec((Vector2){ball.x, ball.y}, ball.radius,(Rectangle){paddle[player1].x, paddle[player1].y, paddle[player1].width, paddle[player1].height}))
        {
            ball.speed_x *= -1;
        }
   
        if(CheckCollisionCircleRec((Vector2){ball.x, ball.y}, ball.radius,(Rectangle){paddle[player2].x, paddle[player2].y, paddle[player2].width, paddle[player2].height}))
        {
            ball.speed_x *= -1;
        }
      
        ClearBackground(BLACK);
        DrawLine(screen_width/2, 0, screen_width/2, screen_height, WHITE);
        DrawRectangle(paddle[player1].x, paddle[player1].y, paddle[player1].width, paddle[player1].height, WHITE);
        DrawRectangle(paddle[player2].x, paddle[player2].y, paddle[player2].width, paddle[player2].height, WHITE);
        DrawCircle(ball.x, ball.y, ball.radius, WHITE);

        EndDrawing();
    }
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
    if(ball->x + ball->radius >=GetScreenWidth() || ball->x - ball->radius <=0)
    {
        ball->speed_x *= -1;
    }
}

void player1Update(Paddle *paddle)
{   //mexer na vertical
    if(IsKeyDown(KEY_W))    paddle->y -= paddle->speed_y;
    if(IsKeyDown(KEY_S))    paddle->y += paddle->speed_y;
    if(paddle->y + paddle->height >= GetScreenHeight())paddle->y = GetScreenHeight() - paddle->height;
    if(paddle->y <= 0) paddle->y = 0;
    //mexer na horizontal
    if(IsKeyDown(KEY_A))    paddle->x -= paddle->speed_x;
    if(IsKeyDown(KEY_D))    paddle->x += paddle->speed_x;
    if(paddle->x <= 0)      paddle->x = 0;
    if(paddle->x + paddle->width >= GetScreenWidth()/2) paddle->x = GetScreenWidth()/2 - paddle->width;
}
void player2Update(Paddle *paddle)
{   //mexer na vertical
    if(IsKeyDown(KEY_UP))    paddle->y -= paddle->speed_y;
    if(IsKeyDown(KEY_DOWN))    paddle->y += paddle->speed_y;
    if(paddle->y + paddle->height >= GetScreenHeight())paddle->y = GetScreenHeight() - paddle->height;
    if(paddle->y <= 0) paddle->y = 0;
    //mexer na horizontal
    if(IsKeyDown(KEY_LEFT))    paddle->x -= paddle->speed_x;
    if(IsKeyDown(KEY_RIGHT))    paddle->x += paddle->speed_x;
    if(paddle->x <= GetScreenWidth()/2) paddle->x = GetScreenWidth()/2;      
    if(paddle->x + paddle->width >= GetScreenWidth()) paddle->x = GetScreenWidth() - paddle->width;
}
void cpuUpdate(Paddle *paddle, Ball ball) //mini IA  pra jogar contra a maquina
{
    if(paddle->y+ paddle->height/2 > ball.y) paddle->y -= paddle->speed_y;
    else paddle->y += paddle->speed_y;
    
    if(paddle->y + paddle->height >= GetScreenHeight())paddle->y = GetScreenHeight() - paddle->height;
    if(paddle->y <= 0) paddle->y = 0;
}