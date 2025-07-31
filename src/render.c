#include <stdio.h>
#include "raylib/raylib.h"
#include "render.h"

#define BACKGROUND_COLOR RAYWHITE

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

	if (vRenderMonitor <= GetMonitorCount()) SetWindowMonitor(vRenderMonitor);

	SetTargetFPS(vRenderFps);
}
void RenderLoop() {
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BACKGROUND_COLOR);

		RenderGrids(3);
		RenderInfo();

		EndDrawing();
	}
}
void RenderGrids(int gridCount) {
	const int blockWidth = RenderGetScaleBlock(0.2f, 10, 200);
	const int blockHeight = RenderGetScaleBlock(0.2f, 10, 200);
	const int spacing = 5;

	int totalWidth = gridCount * blockWidth + (gridCount - 1) * spacing;
	int totalHeight = gridCount * blockHeight + (gridCount - 1) * spacing;

	int xSpace = (GetScreenWidth() - totalWidth) / 2;
	int ySpace = (GetScreenHeight() - totalHeight) / 2;

	for (int i = 0; i < gridCount; i++) {
		for (int j = 0; j < gridCount; j++) {
			int x = xSpace + j * (blockWidth + spacing);
			int y = ySpace + i * (blockHeight + spacing);
			DrawRectangle(x, y, blockWidth, blockHeight, GRAY);
		}
	}
}

void RenderInfo() {
	char fpsTxt[100];
	int posX = 20;
	int posY = 20;
	sprintf(fpsTxt, "FPS: %d", GetFPS());
	DrawText(fpsTxt, posX, posY, 20, BLACK);
}

void RenderClear() {
	CloseWindow();
}

inline int RenderGetScaleBlock(float scale, int minSize, int maxSize) {
	int base = (GetScreenWidth() < GetScreenHeight()) ? GetScreenWidth() : GetScreenHeight();

	int size = (int)(base * scale);
	if (size < minSize) size = minSize;
	if (size > maxSize) size = maxSize;
	return size;
}