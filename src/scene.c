#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "scene.h"
#include "render.h"

GridBlock_t* SceneGridBlocks = NULL;
unsigned int SceneBlockCount = 0;
unsigned int SceneMaxRow = 0, SceneMaxCol = 0;

bool vSceneInitialDraw = false;
unsigned int vSceneCorrectBlocksCount = 0;
bool vSceneTimerStarted = false;
double vSceneStartGameTimer = 0, vSceneLastGameTimer = 0;

bool SceneInit(unsigned int maxRow, unsigned int maxCol) {
	if (maxRow <= 0 || maxCol <= 0)
		return false;
	SceneClearBlocks();
	SceneMaxRow = maxRow;
	SceneMaxCol = maxCol;
	SceneBlockCount = SceneMaxRow * SceneMaxCol;
	if (SceneBlockCount % 2 != 0) {
		printf("Attenzione: la griglia non ha un numero pari di blocchi\n");
		return false;
	}
	return SceneCreatePairsAndShuffle();
}
void SwapBlocks(GridBlock_t* a, GridBlock_t* b) {
	GridBlock_t temp = *a;
	*a = *b;
	*b = temp;
}

bool SceneCreatePairsAndShuffle() {
	SceneGridBlocks = malloc(sizeof(GridBlock_t) * SceneBlockCount);
	if (SceneGridBlocks == NULL) {
		printf("Memoria insufficiente per allocare i blocchi\n");
		SceneBlockCount = 0;
		return false;
	}

	for (unsigned int i = 0; i < SceneBlockCount / 2; i++) {
		SceneGridBlocks[i * 2].number = i;
		SceneGridBlocks[i * 2 + 1].number = i;
	}

	for (int i = 0; i < SceneBlockCount; i++) {
		SceneGridBlocks[i].index = i;
		SceneGridBlocks[i].x = 0;
		SceneGridBlocks[i].y = 0;
		SceneGridBlocks[i].width = 0;
		SceneGridBlocks[i].height = 0;
		SceneGridBlocks[i].color = BLOCK_COLOR_DEFAULT;
		SceneGridBlocks[i].done = false;
		SceneGridBlocks[i].picked = false;
	}
	srand((unsigned int)time(NULL));

	// Fisher-Yates shuffle
	for (int i = SceneBlockCount - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		SwapBlocks(&SceneGridBlocks[i], &SceneGridBlocks[j]);
	}
	return true;
}

void SceneClearBlocks() {
	if (SceneGridBlocks == NULL) return;

	printf("Clearing %u blocks\n", SceneBlockCount);
	free(SceneGridBlocks);
	SceneBlockCount = 0;
}
void SceneInitTimer() {
	vSceneTimerStarted = true;
	vSceneStartGameTimer = GetTime();
}
void SceneEndTimer() {
	vSceneTimerStarted = false;
}
char* SceneGetTimerText() {
	if (!SceneIsRoundWinned())
		vSceneLastGameTimer = GetTime();

	double elapsed = vSceneLastGameTimer - vSceneStartGameTimer;
	int seconds = (int)elapsed % 60;
	int minutes = ((int)elapsed / 60) % 60;
	int hours = (int)elapsed / 3600;

	static char timerText[64];
	sprintf(timerText, "%02d:%02d:%02d", hours, minutes, seconds);
	return timerText;
}

bool SceneIsRoundWinned() {
	return vSceneCorrectBlocksCount == SceneBlockCount;
}
