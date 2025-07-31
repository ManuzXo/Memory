#pragma once
#ifndef _SCENE_
#define _SCENE_
#include <stdbool.h>
#include "struct.h"

//Array di numeri che rappresentano i blocchi della scena
extern int *SceneBlocks;
extern unsigned int SceneBlockCount;
extern unsigned int SceneMaxRow, SceneMaxCol;

// Inizializza la scena con il numero di righe e colonne
extern void SceneInit(unsigned int maxRow, unsigned int maxCol);
// Scambia due blocchi nella scena
extern void SwapBlocks(int* a, int* b);
// Crea coppie di blocchi e li mescola
extern bool SceneCreatePairsAndShuffle();
// Pulisce i blocchi della scena, liberando la memoria
extern void SceneClearBlocks();

#endif // !_SCENE_
