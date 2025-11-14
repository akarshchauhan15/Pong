#define RAYGUI_IMPLEMENTATION
#define _CRT_SECURE_NO_DEPRECATE

#include "raygui.h"
#include "raylib.h"
#include "objects.h"
#include "state.h"

bool Running = true;
bool isPlaying = false;

Paddle PlayerPaddle = Paddle();
CpuPaddle AIPaddle = CpuPaddle();
Ball ball = Ball();


void Startup() {

	//Configuration
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	SetExitKey(KEY_NULL);
	
	//Window
	InitWindow(ScreenSize.x, ScreenSize.y, "Pong");
	SetTargetFPS(120);

	//Audio
	InitAudioDevice();
	LoadSfx();

	//Gui
	GuiSetStyle(DEFAULT, TEXT_SIZE, 48);
	GuiSetStyle(LABEL, TEXT_COLOR_NORMAL, ColorToInt(RAYWHITE));
}

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

void AddScore() {

	if ((ball.Position.x - ball.Radius) >= ScreenSize.x) {
		PlayerPaddle.Score++;
		ball.ResetBall();
	}

	else if ((ball.Position.x + ball.Radius) <= 0) {
		AIPaddle.Score++;
		ball.ResetBall();
	}
}

void MainGameLoop() {

	ClearBackground(BackgroundColor);

	switch (CurrentState) {

	case MENU: {
		DrawMenu();
	} break;

	case PLAYING: {
		//Process
		ball.Update();
		AddScore();
		PlayerPaddle.Move();
		AIPaddle.Move(ball.Position.y);

		//Checking collisions

		bool CollisionWithPlayerPaddle = (CheckCollisionCircleRec(ball.Position, ball.Radius, Rectangle{ PlayerPaddle.Position.x, PlayerPaddle.Position.y, (float)PlayerPaddle.Width, (float)PlayerPaddle.Height }) && ball.Speed.x < 0);
		bool CollisionWithAIPaddle = (CheckCollisionCircleRec(ball.Position, ball.Radius, Rectangle{ AIPaddle.Position.x, AIPaddle.Position.y, (float)AIPaddle.Width, (float)AIPaddle.Height }) && ball.Speed.x > 0);

		if (CollisionWithPlayerPaddle || CollisionWithAIPaddle) {
			ball.Speed.x *= -1;
			ball.Accelerate();
			PlaySound(Collide1);
		}

		DrawGame();

		//Objects
		ball.Draw();
		PlayerPaddle.Draw();
		AIPaddle.Draw();

		DrawScores();
	}break;

	case OPTIONS: {
		DrawOptions();
	}break;

	case EXIT: {
		Running = false;
	}break;
	}

}

int main() {

	Startup();

	//Game
	ball.Speed = ball.DefaultSpeed;
	
	PlayerPaddle.Position = { float(PlayerPaddle.Offset) , PlayerPaddle.Position.y };
	AIPaddle.Position = { ScreenSize.x - float(AIPaddle.Offset) - AIPaddle.Width , AIPaddle.Position.y };

	//Game Loop

	while (Running && WindowShouldClose() == false)
	{
		BeginDrawing();

		MainGameLoop();
		
		EndDrawing();
	}

	CloseAudioDevice();
	CloseWindow();

	return 0;
}