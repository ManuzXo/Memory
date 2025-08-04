#include <stdio.h>
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS 
#include "raylib/raylib.h"
#include "raylib/raygui.h"

#include "scene.h"
#include "render.h"

#define BACKGROUND_COLOR RAYWHITE
#define PADDING_RATIO 0.30f  // 30% padding totale (15% per lato)
#define SPACING_RATIO 0.01f  // 1% dello schermo come spacing
#define TICK_ANIMATION_SECONDS .5f
#define TICK_ANIMATION_FRAME (int)(TICK_ANIMATION_SECONDS * vRenderFps)


unsigned int vRenderMonitor = 0;
unsigned int vRenderFps = 60;
bool vRenderFullscreen = false;
bool vRenderExit = false;
MouseCursor vRenderMouseCursor = MOUSE_CURSOR_DEFAULT;

unsigned int vRenderBlockPickedCount = 0;
GridBlock_t* vRenderBlockChoosed[2] = { NULL };
bool vRenderStartAnimation = false;
int vRenderTickAnimation = 0;

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
	while (!WindowShouldClose() && !vRenderExit) {
		BeginDrawing();
		ClearBackground(BACKGROUND_COLOR);
		RenderMainLogic();
		EndDrawing();
	}
}

inline void RenderMainLogic() {
	if (!vSceneInitialDraw)
	{
		RenderDrawStartAnimation();
	}
	else
	{
		vRenderMouseCursor = MOUSE_CURSOR_DEFAULT;

		RenderUpdateBlocksGrids(SceneMaxRow, SceneMaxCol);
		RenderBlocks();
		RenderCheckResultBlocks();
		RenderCheckAnimationChoosedBlockRestore();

		RenderInfo();
		SetMouseCursor(vRenderMouseCursor);
	}
}
void RenderDrawStartAnimation() {
	const char* text = "Press any key to Start!";
	SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
	DrawText(text, GetScreenWidth() / 2 - MeasureText(text, 20) / 2, GetScreenHeight() / 2 - 10, 20, BLACK);
	vSceneInitialDraw = GetKeyPressed() > 0;
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
			GridBlock_t* block = &SceneGridBlocks[blockIndex];
			if (block == NULL) {
				printf("Il blocco corrente è NULL, index: %i\n", blockIndex);
				return;
			}
			block->x = xBlock;
			block->y = yBlock;
			block->width = blockWidth;
			block->height = blockHeight;
			blockIndex++;
		}
	}
}
void RenderBlocks() {
	for (int i = 0; i < SceneBlockCount; i++) {
		GridBlock_t* block = &SceneGridBlocks[i];
		if (block == NULL) {
			printf("Il blocco corrente è NULL, index: %i\n", i);
			return;
		}
		RenderBlock(block);
		RenderCheckAndSetMousePointingHand(block);
	}
}

void RenderBlock(GridBlock_t* block) {
	GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
	GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
	GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(BLACK));
	GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED, ColorToInt(BLACK));

	GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(block->color));
	GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt(block->color));
	GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt(block->color));
	char* numberTxt = NULL;
	if (block->picked || block->done) numberTxt = TextFormat("%i", block->number);
	if (GuiButton((Rectangle) { block->x, block->y, block->width, block->height }, numberTxt) == 1) {
		RenderSelectBlock(block);
	}
}
void RenderSelectBlock(GridBlock_t* block) {
	if (block->done == false) {
		if (RenderClickedTwoBlocks()) RenderRestoreChoosedBlocks();
		block->color = BLOCK_COLOR_PICKED;
		block->picked = true;
		*(&vRenderBlockChoosed[vRenderBlockPickedCount]) = block;
		vRenderBlockPickedCount++;

	}
}
void RenderCheckResultBlocks() {
	if (!RenderClickedTwoBlocks()) return;

	if (vRenderBlockChoosed[0]->number == vRenderBlockChoosed[1]->number)
	{
		vRenderBlockChoosed[0]->done = true;
		vRenderBlockChoosed[1]->done = true;
		vRenderBlockChoosed[0]->color = BLOCK_COLOR_DONE;
		vRenderBlockChoosed[1]->color = BLOCK_COLOR_DONE;
		RenderRestoreChoosedBlocks();
		vSceneCorrectBlocksCount += 2;
	}
	else if (!vRenderStartAnimation)
	{
		vRenderTickAnimation = TICK_ANIMATION_FRAME;
		vRenderStartAnimation = true;
	}
}
bool RenderClickedTwoBlocks() {
	return vRenderBlockPickedCount == 2;
}
void RenderCheckAnimationChoosedBlockRestore() {
	if (!vRenderStartAnimation) return;
	if (vRenderTickAnimation < 0) RenderRestoreChoosedBlocks();
	vRenderTickAnimation--;
}
void RenderRestoreChoosedBlocks() {
	if (!vRenderBlockChoosed[0]->done && !vRenderBlockChoosed[1]->done) {
		vRenderBlockChoosed[0]->color = BLOCK_COLOR_DEFAULT;
		vRenderBlockChoosed[1]->color = BLOCK_COLOR_DEFAULT;
		vRenderBlockChoosed[0]->picked = false;
		vRenderBlockChoosed[1]->picked = false;
	}
	vRenderBlockPickedCount = 0;
	vRenderBlockChoosed[0] = NULL;
	vRenderBlockChoosed[1] = NULL;

	//resetta l'animazione se è rimasta appesa
	vRenderStartAnimation = false;
}

void RenderCheckAndSetMousePointingHand(GridBlock_t* block) {
	if (RenderMouseIsHoverBlock(block) && vRenderMouseCursor == MOUSE_CURSOR_DEFAULT) vRenderMouseCursor = MOUSE_CURSOR_POINTING_HAND;
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
	static float slider = 0;

	int base = GetScreenWidth() > GetScreenHeight() ? GetScreenWidth() : GetScreenHeight();
	int fontSize = (int)(base * 0.015f);
	int padding = 15;

	char* infoTxt = TextFormat("FPS (%d) | Grid Size (%ix%i)", GetFPS(), SceneMaxRow, SceneMaxCol);
	DrawText(infoTxt, padding, 15, fontSize, BLACK);


	char* timerTxt = GuiIconText(ICON_SAND_TIMER, SceneGetTimerText());
	int timetTxtSize = MeasureText(timerTxt, 20);
	GuiDrawText(timerTxt, (Rectangle) { GetScreenWidth() - timetTxtSize, 10, timetTxtSize, 20 }, 0, BLACK);


	int btnSize = 30;
	int xBtn = GetScreenWidth() - padding - btnSize;
	int yBtn = GetScreenHeight() - padding - btnSize;
	GuiLoadStyleDefault();
	GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
	GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(LIME));
	if (GuiButton((Rectangle) { xBtn - btnSize - 10, yBtn, btnSize, btnSize }, "+") == 1) {
		SceneInit(SceneMaxRow + 2, SceneMaxCol + 2);
	}
	GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(RED));
	if (GuiButton((Rectangle) { xBtn, yBtn, btnSize, btnSize }, "-") == 1) {
		SceneInit(SceneMaxRow - 2, SceneMaxCol - 2);
	}
}
void RenderClear() {
	CloseWindow();
}
