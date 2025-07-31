#include <stdio.h>
#include "raylib/raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raylib/raygui.h"

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
	RenderSetWindowState();
	RenderLoop();
	RenderClear();
}
void RenderSetWindowState() {
	SetTraceLogLevel(LOG_NONE);
	InitWindow(800, 800, "Memory Game!");
	
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
		RenderUpdateBlocksGrids(SceneMaxRow, SceneMaxCol);
		RenderBlocks();
		RenderInfo();
		SetMouseCursor(vRenderMouseCursor);
		EndDrawing();
	}
}
void RenderUpdateBlocksGrids(int maxRow, int maxCol) {
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
			GridBlock_t* currentBlock = &SceneGridBlocks[blockIndex];
			if (currentBlock == NULL) {
				printf("Il blocco corrente è NULL, index: %i\n", blockIndex);
				return;
			}
			currentBlock->x = xBlock;
			currentBlock->y = yBlock;
			currentBlock->width = blockWidth;
			currentBlock->height = blockHeight;
			blockIndex++;
		}
	}
}
void RenderBlocks() {
	for (int i = 0; i < SceneBlockCount; i++) {
		GridBlock_t* currentBlock = &SceneGridBlocks[i];
		if (currentBlock == NULL) {
			printf("Il blocco corrente è NULL, index: %i\n", i);
			return;
		}
		RenderBlock(currentBlock);
	}
}

void RenderBlock(GridBlock_t* block) {
	DrawRectangle(block->x, block->y, block->width, block->height, GRAY);
	if (RenderMouseIsHoverBlock(block)) {
		if (vRenderMouseCursor == MOUSE_CURSOR_DEFAULT) {
			vRenderMouseCursor = MOUSE_CURSOR_POINTING_HAND;
		}
		RenderDrawBlockNumber(block);
	}
}

void RenderDrawBlockNumber(GridBlock_t* block) {
	char* numberText = TextFormat("%i", block->number);
	int textWidth = MeasureText(numberText, 20);
	int xText = block->x + block->width / 2 - textWidth;
	int yText = block->y + block->height / 2 - textWidth;
	DrawText(numberText, xText, yText, 20, BLACK);
}
bool RenderMouseIsHoverBlock(GridBlock_t* block) {
	Vector2 mousePos = GetMousePosition();
	int leftX = block->x;
	int rightX = block->x + block->width;
	int topY = block->y;
	int bottomY = block->y + block->height;
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
