#include <stdio.h>
#include "raylib/raylib.h"
#include "scene.h"
#include "render.h"

#define BACKGROUND_COLOR RAYWHITE
#define PADDING_RATIO 0.30f  // 30% padding totale (15% per lato)
#define SPACING_RATIO 0.01f  // 1% dello schermo come spacing

unsigned int vRenderMonitor = 0;
unsigned int vRenderFps = 60;
bool vRenderFullscreen = false;
bool vRenderExit = false;
MouseCursor vRenderMouseCursor = MOUSE_CURSOR_DEFAULT;

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
	while (!WindowShouldClose() && !vRenderExit)
	{
		BeginDrawing();
		ClearBackground(BACKGROUND_COLOR);
		
		vRenderMouseCursor = MOUSE_CURSOR_DEFAULT;
		RenderGrids(SceneMaxRow, SceneMaxCol);
		RenderInfo();
		SetMouseCursor(vRenderMouseCursor);
		
		EndDrawing();
	}
}
void RenderGrids(int maxRow, int maxCol) {

	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	int paddingX = screenWidth * PADDING_RATIO / 2;
	int paddingY = screenHeight * PADDING_RATIO / 2;

	int availableWidth = screenWidth - 2 * paddingX;
	int availableHeight = screenHeight - 2 * paddingY;

	// Calcola spacing proporzionale allo schermo
	int spacing = screenWidth * SPACING_RATIO;

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
			int xBlock = startX + col * (blockWidth + spacing);
			int yBlock = startY + row * (blockHeight + spacing);

			if (blockIndex >= SceneBlockCount) {
				printf("l'index block locale (%i) supera i blocchi totali (%i)\n", blockIndex, SceneBlockCount);
				return;
			}
			int* currentBlock = &SceneBlocks[blockIndex];
			if (currentBlock == NULL) {
				printf("Il blocco corrente è NULL, index: %i\n", blockIndex);
				return;
			}
			RenderBlock(*currentBlock, xBlock, yBlock, blockWidth, blockHeight);
			blockIndex++;
		}
	}
}

void RenderBlock(int blockNumber, int xBlock, int yBlock, int blockWidth, int blockHeight) {
	DrawRectangle(xBlock, yBlock, blockWidth, blockHeight, GRAY);
	if (RenderMouseIsHoverBlock(xBlock, yBlock, blockWidth, blockHeight)) {
		if (vRenderMouseCursor == MOUSE_CURSOR_DEFAULT) {
			vRenderMouseCursor = MOUSE_CURSOR_POINTING_HAND;
		}
		RenderDrawBlockNumber(blockNumber, xBlock, yBlock, blockWidth, blockHeight);
	}
}
void RenderDrawBlockNumber(int blockNumber, int xBlock, int yBlock, int blockWidth, int blockHeight) {
	char* numberText = TextFormat("%i", blockNumber);
	int textWidth = MeasureText(numberText, 20);
	int xText = xBlock + blockWidth / 2 - textWidth;
	int yText = yBlock + blockHeight / 2 - textWidth;
	DrawText(numberText, xText, yText, 20, BLACK);
}

bool RenderMouseIsHoverBlock(int xBlock, int yBlock, int blockWidth, int blockHeight) {
	Vector2 mousePos = GetMousePosition();
	int leftX = xBlock;
	int rightX = xBlock + blockWidth;
	int topY = yBlock;
	int bottomY = yBlock + blockHeight;
	return mousePos.x >= leftX && mousePos.x <= rightX && mousePos.y >= topY && mousePos.y <= bottomY;
}

void RenderInfo() {
	char infoTxt[100];
	sprintf(infoTxt, "FPS (%d) | Grid Size (%ix%i)", GetFPS(), SceneMaxRow, SceneMaxCol);
	DrawText(infoTxt, 15, 15, 20, BLACK);
}

void RenderClear() {
	CloseWindow();
}
