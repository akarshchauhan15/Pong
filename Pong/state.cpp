#include "raygui.h"
#include "state.h"
#include "objects.h"

GameState CurrentState = GameState::MENU;

float Volume = 0.5f;
bool Fullscreen = false;

void DrawMenu() {
	ClearBackground(BackgroundColor);

	DrawText("Pong", 420, 100, 180, FavorVictoryColor);

	if (GuiButton({ 490, 460, 300, 60 }, "Play"))
		CurrentState = PLAYING;
	else if (GuiButton({ 490, 540, 300, 60 }, "Options"))
		CurrentState = OPTIONS;
	else if (GuiButton({ 490, 620, 300, 60 }, "Exit"))
		CurrentState = EXIT;
}

void DrawOptions() {
	DrawText("Options", 40, 24, 100, FavorVictoryColor);

	/*GuiLabel((Rectangle){ 260, 200, 100, 20 }, "Volume");
                volume = GuiSliderBar((Rectangle){ 360, 200, 200, 20 }, NULL, NULL, volume, 0.0f, 1.0f);

                fullscreen = GuiCheckBox((Rectangle){ 360, 250, 20, 20 }, "Fullscreen", fullscreen);*/

	GuiLabel({ 400, 300, 260, 20 }, "Volume");
	Volume = GuiSliderBar({ 600, 300, 200, 20 }, NULL, NULL, &Volume, 0.0f, 1.0f);
	Fullscreen = GuiCheckBox({ 360, 250, 20, 20 }, "Fullscreen", &Fullscreen);

	if (GuiButton({ 1020, 620, 200, 60 }, "Back"))
		CurrentState = MENU;
}

void DrawGame() {

	DrawCircle(ScreenSize.x / 2, ScreenSize.y / 2, 180, HighlightedCircleColorBack);
	DrawCircle(ScreenSize.x / 2, ScreenSize.y / 2, 80, HighlightedCircleColorFront);
	DrawLine(ScreenSize.x / 2, 0, ScreenSize.x / 2, ScreenSize.y, WHITE); //Seperator

	if (IsKeyPressed(KEY_ESCAPE))
		CurrentState = GameState::MENU;
}