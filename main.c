#include <stdio.h>
#include <raylib.h>

#define WIDTH     800
#define HEIGHT    450
#define MAX_SCORE 10

#define PLAYER_WIDTH  WIDTH/100
#define PLAYER_HEIGHT HEIGHT/5
#define PLAYER_SPEED  10

int main()
{
    int score1 = 0;
    int score2 = 0;

    int player1y = HEIGHT/2;
    int player2y = HEIGHT/2;

    SetTargetFPS(60);
    InitWindow(WIDTH, HEIGHT, "Pong");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        // Рисуем черту по середине
        DrawRectangle(WIDTH/2-WIDTH/100/2, 0, WIDTH / 100, HEIGHT, RAYWHITE);

        // Рисуем счет
        DrawText(TextFormat("%i", score1), WIDTH/4,   0, 20, RAYWHITE);
        DrawText(TextFormat("%i", score2), WIDTH/4*3, 0, 20, RAYWHITE);

        // Рисуем игроков
        DrawRectangle(0,                  player1y-PLAYER_HEIGHT/2, PLAYER_WIDTH, PLAYER_HEIGHT, RED);
        DrawRectangle(WIDTH-PLAYER_WIDTH, player2y-PLAYER_HEIGHT/2, PLAYER_WIDTH, PLAYER_HEIGHT, BLUE);


        if (score1 == MAX_SCORE || score2 == MAX_SCORE)
        {
          DrawText("GAME OVER", WIDTH/2-WIDTH/100/2, HEIGHT/2, 20, RAYWHITE);
        }

        // Управление 1 игрока
        if (IsKeyDown(KEY_W))    {player1y -= PLAYER_SPEED;}
        if (IsKeyDown(KEY_S))    {player1y += PLAYER_SPEED;}
        // Управление 2 игрока
        if (IsKeyDown(KEY_UP))   {player2y -= PLAYER_SPEED;}
        if (IsKeyDown(KEY_DOWN)) {player2y += PLAYER_SPEED;}

        EndDrawing();
    }
    return 0;
}
