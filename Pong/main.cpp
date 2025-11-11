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

		if ((Position.y + Radius) >= ScreenSize.y || (Position.y - Radius) <= 0)
			Speed.y *= -1;
		
		if ((Position.x + Radius) >= ScreenSize.x || (Position.x - Radius) <= 0)
			Speed.x *= -1;
	}
};

class Paddle {
public:
	Vector2 Position;
	int Width;
	int Height;
	int Offset = 10;
	int Speed = 3;
	Color Color = { 109, 194, 185, 255 };

	Paddle(float PositionX = 0, int width = 24, int height = 180) {
		Width = width;
		Height = height;
		Position = { PositionX, (ScreenSize.y - Height)/2 };
	}

	void Draw() {
		DrawRectangle(Position.x, Position.y, Width, Height, Color);
	}

	void Move() {
		if (IsKeyDown(KEY_UP) && Position.y >= 0)
			Position.y -= Speed;
		if (IsKeyDown(KEY_DOWN) && Position.y <= ScreenSize.y - Height)
			Position.y += Speed;
	}
};

//New inherited class derived from Paddle
class CpuPaddle : public Paddle {
public:
	void Move(int BallPositionY) {
		if (Position.y + Height / 2 > BallPositionY && Position.y >= 0)
			Position.y -= Speed;
		else if (Position.y + Height / 2 < BallPositionY && Position.y + Height <= ScreenSize.y)
			Position.y += Speed;
	}
};


Paddle PlayerPaddle = Paddle();
CpuPaddle AIPaddle= CpuPaddle();
Ball ball = Ball(16, { ScreenSize.x / 2, ScreenSize.y / 2 }, { 4, 4 });

int main() {

	//Ready

	Color BackgroundColor = { 8, 94, 73, 255 };

	PlayerPaddle.Position = { float(PlayerPaddle.Offset) , PlayerPaddle.Position.y };
	AIPaddle.Position = { ScreenSize.x - float(AIPaddle.Offset) - AIPaddle.Width , AIPaddle.Position.y};

	InitWindow(ScreenSize.x, ScreenSize.y, "Pong");
	SetTargetFPS(120);

	//Game Loop

	while (WindowShouldClose() == false)
	{
		//Process
		ball.Update();
		PlayerPaddle.Move();
		AIPaddle.Move(ball.Position.y);

		//Checking collisions

		bool CollisionWithPlayerPaddle = CheckCollisionCircleRec(ball.Position, ball.Radius, Rectangle{ PlayerPaddle.Position.x, PlayerPaddle.Position.y, (float)PlayerPaddle.Width, (float)PlayerPaddle.Height });
		bool CollisionWithAIPaddle = CheckCollisionCircleRec(ball.Position, ball.Radius, Rectangle{ AIPaddle.Position.x, AIPaddle.Position.y, (float)AIPaddle.Width, (float)AIPaddle.Height });

		if (CollisionWithPlayerPaddle || CollisionWithAIPaddle)
			ball.Speed.x *= -1;

		BeginDrawing();

		//Drawing objects to screen
		ClearBackground(BackgroundColor);
		ball.Draw(); //Ball

		DrawLine(ScreenSize.x / 2, 0, ScreenSize.x / 2, ScreenSize.y, WHITE); //Seperator

		PlayerPaddle.Draw();
		AIPaddle.Draw();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}