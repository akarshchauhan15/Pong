#include "raylib.h"
#include "objects.h"

Vector2 ScreenSize = { 1280, 720 };
Color BackgroundColor = { 30, 150, 121, 255 };
Color HighlightedCircleColorBack = { 55, 179, 149, 255 };
Color HighlightedCircleColorFront = { 87, 210, 170, 255 };
Color PaddleColor = { 109, 194, 185, 255 };
Color FavorVictoryColor = { 146, 240, 220, 255 };

Ball::Ball(int radius, Vector2 position, Vector2 speed) {
	Radius = radius;
	Position = position;
	Speed = speed;
} 
void Ball::Draw() {
	DrawCircle(Position.x, Position.y, Radius, WHITE);
}
void Ball::Update() {
	Position.x += Speed.x;
	Position.y += Speed.y;

	if ((Position.y + Radius) >= ScreenSize.y || (Position.y - Radius) <= 0)
		Speed.y *= -1;
}
void Ball::ResetBall() {
	Position = { ScreenSize.x / 2, ScreenSize.y / 2 };

	Speed = { Speed.x * (GetRandomValue(0, 1) - 0.5f) * 2, Speed.y * (GetRandomValue(0, 1) - 0.5f) * 2 };
}

Paddle::Paddle(float PositionX, int width, int height) {
	Width = width;
	Height = height;
	Position = { PositionX, (ScreenSize.y - Height) / 2 };

	Offset = 10;
	Speed = 3;
	Score = 0;
}
void Paddle::Draw() {
	Rectangle Rect = { Position.x, Position.y, Width, Height };
	DrawRectangleRounded(Rect, 0.8f, 0, PaddleColor);
}
void Paddle::Move() {
	if (IsKeyDown(KEY_UP) && Position.y >= 0)
		Position.y -= Speed;
	if (IsKeyDown(KEY_DOWN) && Position.y <= ScreenSize.y - Height)
		Position.y += Speed;
}


//New inherited class derived from Paddle
void CpuPaddle::Move(int BallPositionY) {
	if (Position.y + Height / 2 > BallPositionY && Position.y >= 0)
		Position.y -= Speed;
	else if (Position.y + Height / 2 < BallPositionY && Position.y + Height <= ScreenSize.y)
		Position.y += Speed;
}