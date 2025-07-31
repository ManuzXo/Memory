#include <stdio.h>
#include "raylib/raylib.h"
#include "scene.h"
#include "render.h"

#define BACKGROUND_COLOR RAYWHITE

unsigned int vRenderMonitor = 0;
unsigned int vRenderFps = 60;
bool vRenderFullscreen = false;

void RenderInit() {
	InitWindow(800, 800, "Memory Game!");
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

		RenderGrids(SceneMaxRow, SceneMaxCol);
		RenderInfo();

		EndDrawing();
	}
}
void RenderGrids(int maxRow, int maxCol) {
	const float paddingRatio = 0.30f;  // 30% total padding (15% per lato)
	const float spacingRatio = 0.01f;  // 1% dello schermo come spacing

	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	int paddingX = screenWidth * paddingRatio / 2;
	int paddingY = screenHeight * paddingRatio / 2;

	int availableWidth = screenWidth - 2 * paddingX;
	int availableHeight = screenHeight - 2 * paddingY;

	// Calcola spacing proporzionale allo schermo
	int spacing = screenWidth * spacingRatio;

	// Calcola dimensione dinamica blocchi
	int blockWidth = (availableWidth - (maxRow - 1) * spacing) / maxRow;
	int blockHeight = (availableHeight - (maxCol - 1) * spacing) / maxCol;

	// Coord di partenza (già centrate con padding)
	int startX = paddingX;
	int startY = paddingY;

	int blockIndex = 0;
	// Disegna griglia
	for (int row = 0; row < maxRow; row++) {
		for (int col = 0; col < maxCol; col++) {
			int x = startX + col * (blockWidth + spacing);
			int y = startY + row * (blockHeight + spacing);
			
			if (blockIndex >= SceneBlockCount) {
				printf("Non ci sono più blocchi da disegnare\n");
				return;
			}
			GridBlock_t* currentBlock = &SceneBlocks[blockIndex];
			currentBlock->x = x;
			currentBlock->y = x;
			DrawRectangle(x, y, blockWidth, blockHeight, GRAY);

			blockIndex++;
		}
	}
}

void RenderInfo() {
	char infoTxt[100];
	sprintf(infoTxt, "FPS (%d) | Grid Size (%ix%i)", GetFPS(), SceneMaxRow, SceneMaxCol);
	DrawText(infoTxt, 15, 15, 20, BLACK);
}

void RenderClear() {
	CloseWindow();
}
