#include <raylib.h>

Vector2 ScreenSize = { 1280, 720 };

class Ball {
public:
	Vector2 Position;
	Vector2 Speed;
	int Radius;

	Ball(int radius, Vector2 position, Vector2 speed) {
		Radius = radius;
		Position = position;
		Speed = speed;
	}

	void Draw() {
		DrawCircle(Position.x, Position.y, Radius, WHITE);
	}

	void Update() {
		Position.x += Speed.x;
		Position.y += Speed.y;
	}
};

struct {
	int Width = 30;
	int ScreenPadding = 12;
	int Height = 180;
} PaddleValues;

class Paddle {
public:
	int PosY = (ScreenSize.y - PaddleValues.Height) / 2;
};

Paddle LeftPaddle;
Paddle RightPaddle;
Ball ball = Ball(20, { ScreenSize.x / 2, ScreenSize.y / 2 }, { 0, 0 });

int main() {

	//Ready

	Color BackgroundColor = { 8, 94, 73, 255 };
	Color PaddleColor = { 109, 194, 185, 255 };
	Color LineColor = WHITE;

	InitWindow(ScreenSize.x, ScreenSize.y, "Pong");
	SetTargetFPS(60);

	//Game Loop

	while (WindowShouldClose() == false)
	{

		BeginDrawing();

		ClearBackground(BackgroundColor);
		ball.Draw(); //Ball

		DrawLine(ScreenSize.x / 2, 0, ScreenSize.x / 2, ScreenSize.y, WHITE); //Seperator

		DrawRectangle(0 + PaddleValues.ScreenPadding, LeftPaddle.PosY, PaddleValues.Width, PaddleValues.Height, PaddleColor);
		DrawRectangle(ScreenSize.x - PaddleValues.Width - PaddleValues.ScreenPadding, RightPaddle.PosY, PaddleValues.Width, PaddleValues.Height, PaddleColor);

		EndDrawing();

	}

	CloseWindow();
	return 0;
}