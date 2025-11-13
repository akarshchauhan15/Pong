#ifndef OBJECTS_H
#define OBJECTS_H

#include "raylib.h"

extern Vector2 ScreenSize;
extern Color BackgroundColor;
extern Color HighlightedCircleColorBack;
extern Color HighlightedCircleColorFront;
extern Color PaddleColor;
extern Color FavorVictoryColor;

class Ball {
public:
	Vector2 Position;
	Vector2 Speed;
	Vector2 DefaultSpeed;
	int Radius;
	int Acceleration;

	Ball(int radius = 16, Vector2 position = { ScreenSize.x / 2, ScreenSize.y / 2 }, Vector2 speed = { 0, 0 });

	void Draw();
	void Update();
	void ResetBall();
	void Accelerate();
};

class Paddle {
public:
	Vector2 Position;
	int Width;
	int Height;
	int Offset;
	int Speed;
	int Score;

	Paddle(float PositionX = 0, int width = 20, int height = 160);

	void Draw();
	void Move();
};

//New inherited class derived from Paddle
class CpuPaddle : public Paddle {
public:

	CpuPaddle() = default;
	void Move(int BallPositionY);
};

#endif OBJECTS_H