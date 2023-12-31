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
    menu, gameplay_choice, game_pvp, game_pve , final_screen
}; // 1         2             3            4        5

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
//initialize left player--------------------------------------------------------------------------------------------
    Paddle paddle[2];
    paddle[player1].x=10;
    paddle[player1].y=screen_height/2 - 60;
    paddle[player1].width=25;
    paddle[player1].height= 120;
    paddle[player1].speed_x=2;
    paddle[player1].speed_y=6;
//initialize right player---------------------------------------------------------------------------------------------
    paddle[player2].x=screen_width - 35;
    paddle[player2].y=screen_height/2 - 60;
    paddle[player2].width=25;
    paddle[player2].height=120;
    paddle[player2].speed_x=2;
    paddle[player2].speed_y=6;
//game phases---------------------------------------------------------------------------------------------------------
    int game_phase=0;
    int choice; //variavel p ver se vai pro pve ou pro pvp
    InitWindow(screen_width, screen_height, "Pongpong");
//menu things---------------------------------------------------------------------------------------------------------
    const char msg1[50] = "MENU";
    const char msg2[50] = "...Pressione [ENTER] para jogar...";

    Font font = LoadFont("C:\\raylib\\raylib\\examples\\text\\resources\\custom_alagard.png");        // Font loading

    Vector2 fontPosition1 = { screen_width/2.0f - MeasureTextEx(font, msg1, (float)font.baseSize * 3, -3).x/2,
                            font.baseSize/2.0f + 150.0f };

    Vector2 fontPosition2 = { screen_width/2.0f - MeasureTextEx(font, msg2, (float)font.baseSize, -2.0f).x/2.0f,
                              screen_height/2.0f - font.baseSize/2.0f - 10.0f };
//gamechoice things---------------------------------------------------------------------------------------------------
    const char msg3[50] = "       Pressione [F1]\npara jogar singleplayer...";
    const char msg4[50] = "       Pressione [F2]\npara jogar multiplayer...";
    Vector2 fontPosition3 = { screen_width/4.0f - MeasureTextEx(font, msg3, (float)font.baseSize, -3).x/2,
                            screen_height/2.0f - font.baseSize/2.0f};

    Vector2 fontPosition4 = { screen_width/1.33f - MeasureTextEx(font, msg4, (float)font.baseSize, -2.0f).x/2.0f,
                              screen_height/2.0f - font.baseSize/2.0f};
//--------------------------------------------------------------------------------------------------------------------
    
    Image radialGradient = GenImageGradientRadial(screen_width, screen_height, 0.0f, WHITE, BLACK);
    Texture2D texture = LoadTextureFromImage(radialGradient);
    UnloadImage(radialGradient);
//------------------------------------
//GAMEWIN TEXTS-------------------------------------------------------------------------------------------------------
    const char msg5[50] = "O player 1 venceu!";
    const char msg6[50] = "O player 2 venceu!";
    const char msg7[50] = "...Pressione [ENTER] para jogar novamente...";
    const char msg8[50] = "   Voce venceu!!";
    const char msg9[50] = "   Voce perdeu :(";
    Vector2 fontPosition5 = { screen_width/2.0f - MeasureTextEx(font, msg5, (float)font.baseSize*2, -3).x/2,
                            screen_height/2-font.baseSize/2.0f};

    Vector2 fontPosition7 = { screen_width/2.0f - MeasureTextEx(font, msg7, (float)font.baseSize, -2.0f).x/2.0f,
                              screen_height/2.0f + font.baseSize/2.0f + 100.0f };
    Image radialGradient1 = GenImageGradientRadial(screen_width, screen_height, 0.0f, WHITE, MAROON);
    Texture2D texture1 = LoadTextureFromImage(radialGradient1);
    UnloadImage(radialGradient1);
    Image radialGradient2 = GenImageGradientRadial(screen_width, screen_height, 0.0f, WHITE, SKYBLUE);
    Texture2D texture2 = LoadTextureFromImage(radialGradient2);
    UnloadImage(radialGradient2);
//----------------------------------------------------------------------------------------------------------------------
//MUSIC AND SOUNDS EFFECTS!!--------------------------------------------------------------------------------------------
    InitAudioDevice();
    Sound popup = LoadSound("C:\\Users\\bruno\\Desktop\\Pong\\Pong_files\\resources\\popup.wav");
    Music gameplay = LoadMusicStream("C:\\Users\\bruno\\Desktop\\Pong\\Pong_files\\resources\\gameplay.mp3");
    Music menuM = LoadMusicStream("C:\\Users\\bruno\\Desktop\\Pong\\Pong_files\\resources\\menu.mp3");
    PlayMusicStream(gameplay);
    PlayMusicStream(menuM);
    SetMusicVolume(gameplay, 0.15f);
    SetMusicVolume(menuM, 0.6f);
    SetSoundVolume(popup, 0.4f);
//----------------------------------------------------------------------------------------------------------------------
    bool playing = false;
    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
    if(playing==true)
    {
        StopMusicStream(gameplay);
        PlayMusicStream(menuM);
        UpdateMusicStream(menuM);
    }
    else if(playing==false)
    {
        StopMusicStream(menuM);
        PlayMusicStream(gameplay);
        UpdateMusicStream(gameplay);
    }
    BeginDrawing();
    switch(game_phase)
    {      
        case menu:
        {
            playing = true;
            ClearBackground(RAYWHITE);
            DrawTexture(texture, 0, 0, WHITE);
            DrawTextEx(font, msg1, fontPosition1, (float)font.baseSize * 3, -3, WHITE);
            DrawTextEx(font, msg2, fontPosition2, (float)font.baseSize, -2, WHITE);
            if(IsKeyPressed(KEY_ENTER)) game_phase++;
        }break;
        case gameplay_choice: 
        {
            playing = true;
            ClearBackground(SKYBLUE);
            DrawRectangle(screen_width/2, 0, screen_width/2, screen_height, MAROON);
            DrawTextEx(font, msg3, fontPosition3, (float)font.baseSize, -3, WHITE);
            DrawTextEx(font, msg4, fontPosition4, (float)font.baseSize, -2, WHITE);
            if(IsKeyPressed(KEY_F1))
            {
                choice=3;
                game_phase=choice;
            }
            else if(IsKeyPressed(KEY_F2))
            {  
                choice=2;
                game_phase=choice;
            }
        }break;
        case game_pvp:
        {   //atualizar as posições
            playing = false;
            ballUpdate(&ball);
            player1Update(&paddle[player1]);
            player2Update(&paddle[player2]);
            if(CheckCollisionCircleRec((Vector2){ball.x, ball.y}, ball.radius,(Rectangle){paddle[player1].x, paddle[player1].y, paddle[player1].width, paddle[player1].height}))
            {
                PlaySound(popup);
                ball.speed_x *= -1.1;
            }
            if(CheckCollisionCircleRec((Vector2){ball.x, ball.y}, ball.radius,(Rectangle){paddle[player2].x, paddle[player2].y, paddle[player2].width, paddle[player2].height}))
            {
                PlaySound(popup);
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
        }break;
        case game_pve:
        {
            playing = false;
            ballUpdate(&ball);
            player1Update(&paddle[player1]);
            cpuUpdate(&paddle[player2], ball);
            if(CheckCollisionCircleRec((Vector2){ball.x, ball.y}, ball.radius,(Rectangle){paddle[player1].x, paddle[player1].y, paddle[player1].width, paddle[player1].height}))
            {
                PlaySound(popup);
                ball.speed_x *= -1.15;
                paddle[player1].speed_y += 0.6;
            }
            if(CheckCollisionCircleRec((Vector2){ball.x, ball.y}, ball.radius,(Rectangle){paddle[player2].x, paddle[player2].y, paddle[player2].width, paddle[player2].height}))
            {
                PlaySound(popup);
                ball.speed_x *= -1;
            }
            ClearBackground(Dark_Green);
            DrawRectangle(screen_width/2, 0, screen_width/2, screen_height, Green);
            DrawCircle(screen_width/2, screen_height/2, 150, Light_Green);
            DrawLine(screen_width/2, 0, screen_width/2, screen_height, WHITE);
            DrawRectangleRounded((Rectangle){paddle[player1].x, paddle[player1].y, paddle[player1].width, paddle[player1].height}, 1, 0, MAROON);
            DrawRectangleRounded((Rectangle){paddle[player2].x, paddle[player2].y, paddle[player2].width, paddle[player2].height}, 1, 0, DARKBLUE);
            DrawCircle(ball.x, ball.y, ball.radius, Yellow);
            DrawText(TextFormat("%i", ball.score_player1), screen_width/4 -20, 20, 80, WHITE);
            DrawText(TextFormat("%i", ball.score_player2), 3*screen_width/4 -20, 20, 80, WHITE);

            if(ball.score_player1 >= 3 || ball.score_player2>=3) game_phase = final_screen;
        }break;
        case final_screen:
        {
            playing = true;
            if(choice==3)//single player
            {
                if(ball.score_player1>ball.score_player2) 
                {
                ClearBackground(RAYWHITE);
                DrawTexture(texture1, 0, 0, WHITE);
                DrawTextEx(font, msg8, fontPosition5, (float)font.baseSize * 2, -3, WHITE);
                DrawTextEx(font, msg7, fontPosition7, (float)font.baseSize, -2, WHITE);
                }
                else if(ball.score_player2>ball.score_player1)
                {
                ClearBackground(RAYWHITE);
                DrawTexture(texture2, 0, 0, WHITE);
                DrawTextEx(font, msg9, fontPosition5, (float)font.baseSize * 2, -3, WHITE);
                DrawTextEx(font, msg7, fontPosition7, (float)font.baseSize, -2, WHITE);
                }
            }
            else if(choice==2) //mutiplayer
            {
                if(ball.score_player1>ball.score_player2) 
                {
                ClearBackground(RAYWHITE);
                DrawTexture(texture1, 0, 0, WHITE);
                DrawTextEx(font, msg5, fontPosition5, (float)font.baseSize * 2, -3, WHITE);
                DrawTextEx(font, msg7, fontPosition7, (float)font.baseSize, -2, WHITE);
                }
                else if(ball.score_player2>ball.score_player1)
                {
                ClearBackground(RAYWHITE);
                DrawTexture(texture2, 0, 0, WHITE);
                DrawTextEx(font, msg6, fontPosition5, (float)font.baseSize * 2, -3, WHITE);
                DrawTextEx(font, msg7, fontPosition7, (float)font.baseSize, -2, WHITE);
                }
            }

            if(IsKeyPressed(KEY_ENTER))
            {
                game_phase = choice;
                ball.score_player1 = 0;
                ball.score_player2 = 0;
            }
        }break;
        }
        EndDrawing();
    }
    UnloadMusicStream(gameplay);
    UnloadMusicStream(menuM);
    UnloadSound(popup);

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
    ball->speed_x = 7*speed_choices[GetRandomValue(0,1)];
    ball->speed_y = 7*speed_choices[GetRandomValue(0,1)];
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