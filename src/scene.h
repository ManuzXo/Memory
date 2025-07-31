#pragma once
#ifndef _SCENE_
#define _SCENE_
#include <stdbool.h>
#include "struct.h"

extern GridBlock_t *SceneBlocks;
extern unsigned int SceneBlockCount;
extern unsigned int SceneMaxRow, SceneMaxCol;

extern void SceneInit(unsigned int maxRow, unsigned int maxCol);
extern bool SceneAddBlock(int x, int y, Color color);
extern void SceneClearBlocks();
#endif // !_SCENE_
