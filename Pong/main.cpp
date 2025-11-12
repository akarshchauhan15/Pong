#include "raylib.h"
#include "objects.h"

bool isPlaying = false;

Paddle PlayerPaddle = Paddle();
CpuPaddle AIPaddle = CpuPaddle();
Ball ball = Ball();


void DrawScores() {

	Color PlayerColor = WHITE;
	Color AIColor = WHITE;

	if (PlayerPaddle.Score > AIPaddle.Score)
		PlayerColor = FavorVictoryColor;
	else if (AIPaddle.Score > PlayerPaddle.Score)
		AIColor = FavorVictoryColor;

	DrawText(TextFormat("%i", PlayerPaddle.Score), ScreenSize.x / 4 - 20, 20, 80, PlayerColor);
	DrawText(TextFormat("%i", AIPaddle.Score), 3 * ScreenSize.x / 4 - 20, 20, 80, AIColor);
}

int main() {

	//Ready
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	InitWindow(ScreenSize.x, ScreenSize.y, "Pong");
	SetTargetFPS(120);

	ball.Speed = { 4, 4 };

	PlayerPaddle.Position = { float(PlayerPaddle.Offset) , PlayerPaddle.Position.y };
	AIPaddle.Position = { ScreenSize.x - float(AIPaddle.Offset) - AIPaddle.Width , AIPaddle.Position.y};

	//Game Loop

	while (WindowShouldClose() == false)
	{
		//Process
		ball.Update();
		PlayerPaddle.Move();
		AIPaddle.Move(ball.Position.y);

		//Checking collisions

		bool CollisionWithPlayerPaddle = (CheckCollisionCircleRec(ball.Position, ball.Radius, Rectangle{ PlayerPaddle.Position.x, PlayerPaddle.Position.y, (float)PlayerPaddle.Width, (float)PlayerPaddle.Height }) && ball.Speed.x < 0);
		bool CollisionWithAIPaddle = (CheckCollisionCircleRec(ball.Position, ball.Radius, Rectangle{ AIPaddle.Position.x, AIPaddle.Position.y, (float)AIPaddle.Width, (float)AIPaddle.Height }) && ball.Speed.x > 0);

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
