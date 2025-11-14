#include "raylib.h"
#include "raymath.h"
#include "objects.h"

Vector2 ScreenSize = { 1280, 720 };
Color BackgroundColor = { 30, 150, 121, 255 };
Color HighlightedCircleColorBack = { 55, 179, 149, 255 };
Color HighlightedCircleColorFront = { 87, 210, 170, 255 };
Color PaddleColor = { 109, 194, 185, 255 };
Color FavorVictoryColor = { 146, 240, 220, 255 };

Sound Collide1;
Sound Collide2;

void LoadSfx() {
	Collide1 = LoadSound("Assets/Sounds/Collide1.wav");
	Collide2 = LoadSound("Assets/Sounds/Collide2.wav");

	SetSoundVolume(Collide1, 0.6f);
	SetSoundVolume(Collide2, 0.6f);
}

Ball::Ball(int radius, Vector2 position, Vector2 speed) {
	Radius = radius;
	Position = position;
	Speed = speed;

	DefaultSpeed = {360, 360};
	Acceleration = 20;
} 
void Ball::Draw() {
	DrawCircle(Position.x, Position.y, Radius, WHITE);
}
void Ball::Update() {
	Position.x += Speed.x * GetFrameTime();
	Position.y += Speed.y * GetFrameTime();

	if ((Position.y + Radius) >= ScreenSize.y || (Position.y - Radius) <= 0) {
		Speed.y *= -1;
		PlaySound(Collide2);
	}
}
void Ball::ResetBall() {
	Position = { ScreenSize.x / 2, ScreenSize.y / 2 };

	Speed = { DefaultSpeed.x * (GetRandomValue(0, 1) - 0.5f) * 2, DefaultSpeed.y * (GetRandomValue(0, 1) - 0.5f) * 2 };
}
void Ball::Accelerate() {
	Speed.x += Acceleration * (abs(int(Speed.x)) / Speed.x);
	Speed.y += Acceleration * (abs(int(Speed.y)) / Speed.y);
}



Paddle::Paddle(float PositionX, int width, int height) {
	Width = width;
	Height = height;
	Position = { PositionX, (ScreenSize.y - Height) / 2 };

	Offset = 10;
	Speed = 320;
	Score = 0;
}
void Paddle::Draw() {
	Rectangle Rect = { Position.x, Position.y, Width, Height };
	DrawRectangleRounded(Rect, 0.8f, 0, PaddleColor);
}
void Paddle::Move() {
	if (IsKeyDown(KEY_UP) && Position.y >= Offset)
		Position.y -= Speed * GetFrameTime();
	if (IsKeyDown(KEY_DOWN) && Position.y <= ScreenSize.y - Height - Offset)
		Position.y += Speed * GetFrameTime();
}



//New inherited class derived from Paddle
void CpuPaddle::Move(int BallPositionY) {
	if (Position.y + Height / 2 > BallPositionY && Position.y >= 0)
		Position.y -= Speed * GetFrameTime();
	else if (Position.y + Height / 2 < BallPositionY && Position.y + Height <= ScreenSize.y)
		Position.y += Speed * GetFrameTime();
}