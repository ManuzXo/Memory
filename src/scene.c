#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "scene.h"
#include "render.h"

int* SceneBlocks = NULL;
unsigned int SceneBlockCount = 0;
unsigned int SceneMaxRow = 0, SceneMaxCol = 0;

void SceneInit(unsigned int maxRow, unsigned int maxCol) {
    SceneClearBlocks();
	SceneMaxRow = maxRow;
	SceneMaxCol = maxCol;
	SceneBlockCount = SceneMaxRow * SceneMaxCol;
	if (SceneBlockCount % 2 != 0) {
		printf("Attenzione: la griglia non ha un numero pari di blocchi\n");
		return;
	}
    SceneCreatePairsAndShuffle();
}
void SwapBlocks(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

bool SceneCreatePairsAndShuffle() {
    SceneBlocks = realloc(SceneBlocks, sizeof(int) * SceneBlockCount);
    if (SceneBlocks == NULL) {
        printf("Memoria insufficiente per allocare i blocchi\n");
        SceneBlockCount = 0;
        return false;
    }

    for (unsigned int i = 0; i < SceneBlockCount / 2; i++) {
        SceneBlocks[i * 2] = i;
        SceneBlocks[i * 2 + 1] = i;
    }

    srand((unsigned int)time(NULL));

    // Fisher-Yates shuffle
    for (int i = SceneBlockCount - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        SwapBlocks(&SceneBlocks[i], &SceneBlocks[j]);
    }
    return true;
}

void SceneClearBlocks() {
	if (SceneBlocks == NULL) return;

	printf("Clearing %u blocks\n", SceneBlockCount);
	free(SceneBlocks);
    SceneBlockCount = 0;
}
