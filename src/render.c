#include <stdio.h>
#include "raylib/raylib.h"
#include "render.h"

unsigned int vRenderMonitor = 0;

void RenderInit() {
	InitWindow(800, 800, "Basic Window");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	
	if (vRenderMonitor <= GetMonitorCount())
		SetWindowMonitor(vRenderMonitor);

	SetTargetFPS(60);

	RenderLoop();
	RenderClear();
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