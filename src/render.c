#include <stdio.h>
#include "raylib/raylib.h"
#include "render.h"

unsigned int vRenderMonitor = 0;
unsigned int vRenderFps = 60;
bool vRenderFullscreen = false;

void RenderInit() {
	InitWindow(800, 800, "Basic Window");

	RenderSetWindowState();

	RenderLoop();
	RenderClear();
}
void RenderSetWindowState() {
	unsigned int flags = FLAG_WINDOW_RESIZABLE;
	if (vRenderFullscreen == true) flags |= FLAG_FULLSCREEN_MODE;
	SetWindowState(flags);

	if (vRenderMonitor <= GetMonitorCount())
		SetWindowMonitor(vRenderMonitor);
	
	SetTargetFPS(vRenderFps);
}
void RenderLoop() {
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		RenderInfo();
		EndDrawing();
	}
}
void RenderInfo() {
	char fpsTxt[100];
	int posX = (GetScreenWidth() / 2) - (sizeof(fpsTxt) / 2);
	int posY = GetScreenHeight() / 2;
	sprintf(fpsTxt, "FPS: %d", GetFPS());
	DrawText(fpsTxt, posX, posY, 20, BLACK);
}

void RenderClear() {
	CloseWindow();
}