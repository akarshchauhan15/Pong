#ifndef STATE_H
#define STATE_H

typedef enum {
	MENU,
	PLAYING,
	OPTIONS,
	EXIT
} GameState;


extern float Volume;
extern bool Fullscreen;
extern float Vsync;

extern GameState CurrentState;

void DrawMenu();
void DrawOptions();
void DrawGame();

#endif