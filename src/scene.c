#include <stdlib.h>
#include <stdio.h>
#include "scene.h"
#include "render.h"

GridBlock_t* SceneBlocks = NULL;
unsigned int SceneBlockCount = 0;
unsigned int SceneMaxRow = 0, SceneMaxCol = 0;

void SceneInit(unsigned int maxRow, unsigned int maxCol) {
	SceneClearBlocks();

	SceneMaxRow = maxRow;
	SceneMaxCol = maxCol;
	printf("SceneInit maxRow(%d) & maxCol(%d)\n", maxRow, maxCol);
	for (int i = 0; i < maxRow; i++) {
		for (int j = 0; j < maxCol; j++) {
			if (!SceneAddBlock(0, 0, RED))
				return;
		}
	}
	printf("SceneBlockCount %i\n", SceneBlockCount);

	RenderInit();
	SceneClearBlocks();
}
bool SceneAddBlock(int x, int y, Color color) {
	SceneBlocks = (GridBlock_t*)realloc(SceneBlocks, sizeof(GridBlock_t) * (SceneBlockCount + 1));
	if (SceneBlocks == NULL) {
		printf("Allocazione della memoria non riuscita per il blocco\n");
		return false;
	}
	SceneBlockCount++;
	GridBlock_t* lastBlock = &SceneBlocks[SceneBlockCount - 1];
	lastBlock->x = x;
	lastBlock->y = y;
	lastBlock->color = color;
	return true;
}

void SceneClearBlocks() {
	if (SceneBlocks == NULL) return;

	printf("Clearing %u blocks\n", SceneBlockCount);
	free(SceneBlocks);
}