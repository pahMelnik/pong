#include <assert.h>
#include <math.h>
#include <raylib.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 450
#define MAX_SCORE 10

#define PLAYER_WIDTH WIDTH / 100
#define PLAYER_HEIGHT HEIGHT / 5
#define PLAYER_SPEED 10

#define BALL_SPEED 5
#define BAll_RADIUS 10
#define BALL_COLOR RAYWHITE

#define UP 1
#define DOWN 2

struct Player {
  int x, y, score;
  Color color;
};

struct Ball {
  int x, y;
  float speed;
  Vector2 direction;
};

// TODO запускать в лево и в право с разбросом в 90 градусов
Vector2 random_direction() {
  // Генерируем вектор от -1 до 1
  float x = (float)random() / RAND_MAX * 2 - 1;
  float y = (float)random() / RAND_MAX * 2 - 1;

  // Нормализуем значения
  float vec_len = sqrt(x * x + y * y);
  x = x / vec_len;
  y = y / vec_len;
  Vector2 v = {x, y};
  return v;
}

void draw_ball(struct Ball b) { DrawCircle(b.x, b.y, BAll_RADIUS, BALL_COLOR); }

void reset_ball(struct Ball *b) {
  b->x = WIDTH / 2;
  b->y = HEIGHT / 2;
  b->direction = random_direction();
}

void update_ball_direction(struct Ball *b, struct Player *p1,
                           struct Player *p2) {
  // мяч врезался в игрока 1
  if (b->x <= PLAYER_WIDTH && b->y >= p1->y - PLAYER_HEIGHT / 2 &&
      b->y <= p1->y + PLAYER_HEIGHT / 2) {
    b->direction.x *= -1;

    // Мяч врезался в игрока 2
  } else if (b->x >= WIDTH - PLAYER_WIDTH &&
             b->y >= p2->y - PLAYER_HEIGHT / 2 &&
             b->y <= p2->y + PLAYER_HEIGHT / 2) {
    b->direction.x *= -1;

    // Мяч врезался в верхнюю или нижнюю границу
  } else if (b->y <= 0 || b->y >= HEIGHT) {
    b->direction.y *= -1;

    // Мяч ударился в левую границу
  } else if (b->x <= 0) {
    reset_ball(b);
    p2->score++;

    // Мяч ударился в правую границу
  } else if (b->x >= WIDTH) {
    reset_ball(b);
    p1->score++;
  }
}

void move_ball(struct Ball *b, struct Player *p1, struct Player *p2) {
  update_ball_direction(b, p1, p2);
  b->x += b->speed * b->direction.x;
  b->y += b->speed * b->direction.y;
}

void draw_player(struct Player p) {
  DrawRectangle(p.x, p.y - PLAYER_HEIGHT / 2, PLAYER_WIDTH, PLAYER_HEIGHT,
                p.color);
}

void move_player(struct Player *p, int dir) {
  switch (dir) {
  case UP:
    if (p->y > 0) {
      p->y -= PLAYER_SPEED;
    }
    return;
  case DOWN:
    if (p->y < HEIGHT) {
      p->y += PLAYER_SPEED;
    }
    return;
  }
  assert(false && "UNKNOWN DIRECTION");
}

int main() {
  struct Player player1 = {0, HEIGHT / 2, 0, BLUE};
  struct Player player2 = {WIDTH - PLAYER_WIDTH, HEIGHT / 2, 0, RED};

  struct Ball ball = {
      .x = WIDTH / 2,
      .y = HEIGHT / 2,
      .speed = BALL_SPEED,
      .direction = random_direction(),
  };

  SetTargetFPS(60);
  InitWindow(WIDTH, HEIGHT, "Pong");
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    // Рисуем черту по середине
    DrawRectangle(WIDTH / 2 - WIDTH / 100 / 2, 0, WIDTH / 100, HEIGHT,
                  RAYWHITE);

    // Рисуем счет
    DrawText(TextFormat("%i", player1.score), WIDTH / 4, 0, 20, RAYWHITE);
    DrawText(TextFormat("%i", player2.score), WIDTH / 4 * 3, 0, 20, RAYWHITE);

    // Рисуем игроков
    draw_player(player1);
    draw_player(player2);

    draw_ball(ball);
    move_ball(&ball, &player1, &player2);

    if (player1.score == MAX_SCORE || player2.score == MAX_SCORE) {
      DrawText("GAME OVER", WIDTH / 2 - WIDTH / 100 / 2, HEIGHT / 2, 20,
               RAYWHITE);
    }

    // Управление 1 игрока
    if (IsKeyDown(KEY_W)) {
      move_player(&player1, UP);
    }
    if (IsKeyDown(KEY_S)) {
      move_player(&player1, DOWN);
    }
    // Управление 2 игрока
    if (IsKeyDown(KEY_UP)) {
      move_player(&player2, UP);
    }
    if (IsKeyDown(KEY_DOWN)) {
      move_player(&player2, DOWN);
    }
    if (IsKeyPressed(KEY_R)) {
      reset_ball(&ball);
    }

    EndDrawing();
  }
  return 0;
}
