#include <raylib.h>

Vector2 ScreenSize = { 1280, 720 };

int PlayerScore = 0;
int AIScore = 0;

bool isPlaying = false;

Color BackgroundColor = { 30, 150, 121, 255 };
Color HighlightedCircleColorBack = { 55, 179, 149, 255 };
Color HighlightedCircleColorFront = { 87, 210, 170, 255 };
Color PaddleColor = { 109, 194, 185, 255 };
Color FavorVictoryColor = { 146, 240, 220, 255 };

class Ball {
public:
	Vector2 Position;
	Vector2 Speed;
	int Radius;

	Ball(int radius = 16, Vector2 position = { ScreenSize.x / 2, ScreenSize.y / 2 }, Vector2 speed = { 0, 0 }) {
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


		if ((Position.x - Radius) >= ScreenSize.x) {
			PlayerScore++;
			ResetBall();
		}
			
		else if ((Position.x + Radius) <= 0) {
			AIScore++;
			ResetBall();
		}
	}
	
	void ResetBall() {
		Position = { ScreenSize.x / 2, ScreenSize.y / 2 };

		Speed = { Speed.x * (GetRandomValue(0, 1) - 0.5f) * 2, Speed.y * (GetRandomValue(0, 1) - 0.5f) * 2 };
	}
};

class Paddle {
public:
	Vector2 Position;
	int Width;
	int Height;
	int Offset = 10;
	int Speed = 3;

	Paddle(float PositionX = 0, int width = 20, int height = 160) {
		Width = width;
		Height = height;
		Position = { PositionX, (ScreenSize.y - Height)/2 };
	}

	void Draw() {
		//DrawRectangle(Position.x, Position.y, Width, Height, Color);
		Rectangle Rect = { Position.x, Position.y, Width, Height };
		DrawRectangleRounded(Rect, 0.8f, 0, PaddleColor);
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

void DrawScores() {

	Color PlayerColor = WHITE;
	Color AIColor = WHITE;

	if (PlayerScore > AIScore)
		PlayerColor = FavorVictoryColor;
	else if (AIScore > PlayerScore)
		AIColor = FavorVictoryColor;

	DrawText(TextFormat("%i", PlayerScore), ScreenSize.x / 4 - 20, 20, 80, PlayerColor);
	DrawText(TextFormat("%i", AIScore), 3 * ScreenSize.x / 4 - 20, 20, 80, AIColor);
}

Paddle PlayerPaddle = Paddle();
CpuPaddle AIPaddle = CpuPaddle();
Ball ball = Ball();

int main() {

	//Ready
	ball.Speed = { 4, 4 };

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

		//Decorations
		DrawCircle(ScreenSize.x / 2, ScreenSize.y / 2, 180, HighlightedCircleColorBack);
		DrawCircle(ScreenSize.x / 2, ScreenSize.y / 2, 80, HighlightedCircleColorFront);
		DrawLine(ScreenSize.x / 2, 0, ScreenSize.x / 2, ScreenSize.y, WHITE); //Seperator

		//Objects
		ball.Draw();
		PlayerPaddle.Draw();
		AIPaddle.Draw();

		DrawScores();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
