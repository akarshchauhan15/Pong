#include "raygui.h"
#include "state.h"
#include "raymath.h"
#include "objects.h"

GameState CurrentState = GameState::MENU;

float Volume = 0.5f;
bool Fullscreen = false;
float Vsync = 18;

void DrawMenu() {

	ClearBackground(BackgroundColor);

	DrawText("Pong", 420, 100, 180, FavorVictoryColor);

	if (GuiButton({ 490, 460, 300, 60 }, "Play") || IsKeyPressed(KEY_ENTER))
		CurrentState = PLAYING;
	else if (GuiButton({ 490, 540, 300, 60 }, "Options"))
		CurrentState = OPTIONS;
	else if (GuiButton({ 490, 620, 300, 60 }, "Exit"))
		CurrentState = EXIT;
}

void DrawOptions() {
	DrawText("Options", 40, 24, 100, FavorVictoryColor);

	//Volume
	GuiLabel({ 400, 240, 260, 20 }, "Volume");
	GuiSliderBar({ 600, 240, 200, 20 }, NULL, NULL, &Volume, 0.0f, 1.0f);
	GuiLabel({ 840, 240, 260, 20 }, TextFormat("%.0f", Volume * 100));

	//Fullscreen
	GuiLabel({ 360, 320, 260, 20 }, "Fullscreen");
	GuiCheckBox({ 680, 310, 40, 40 }, NULL, &Fullscreen);

	//Vsync
	GuiLabel({ 376, 400, 300, 20 }, "Max FPS");
	GuiSliderBar({ 600, 400, 200, 20 }, NULL, NULL, &Vsync, 0, 30); // FPS = 30 + Val * 5
	GuiLabel({ 840, 400, 260, 20 }, TextFormat("%.0f", 30 + roundf(Vsync) * 5));

	DrawText("v0.1.0", 20, 680, 32, FavorVictoryColor);

	if (GuiButton({ 800, 620, 200, 60 }, "Apply") || IsKeyPressed(KEY_ENTER)) {
		SetMasterVolume(Volume);
		if (Fullscreen != IsWindowFullscreen()) {
			ToggleFullscreen();
		}
		SetTargetFPS(30 + roundf(Vsync) * 5);
	}

	if (GuiButton({ 1020, 620, 200, 60 }, "Back") || IsKeyPressed(KEY_ESCAPE))
		CurrentState = MENU;
}

void DrawGame() {

	DrawCircle(ScreenSize.x / 2, ScreenSize.y / 2, 180, HighlightedCircleColorBack);
	DrawCircle(ScreenSize.x / 2, ScreenSize.y / 2, 80, HighlightedCircleColorFront);
	DrawLine(ScreenSize.x / 2, 0, ScreenSize.x / 2, ScreenSize.y, WHITE); //Seperator

	if (IsKeyPressed(KEY_ESCAPE))
		CurrentState = GameState::MENU;
}