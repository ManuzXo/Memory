#pragma once
#ifndef _SCENE_
#define _SCENE_
#include <stdbool.h>
#include "struct.h"

// Array di blocchi con coordinate e dimensioni
extern GridBlock_t* SceneGridBlocks;
extern unsigned int SceneBlockCount;
extern unsigned int SceneMaxRow, SceneMaxCol;

extern bool vSceneInitialDraw;
extern unsigned int vSceneCorrectBlocksCount;
extern bool vSceneTimerStarted;
extern double vSceneStartGameTimer, vSceneLastGameTimer;

// Inizializza la scena con il numero di righe e colonne
extern bool SceneInit(unsigned int maxRow, unsigned int maxCol);
// Scambia due blocchi nella scena
extern void SwapBlocks(GridBlock_t* a, GridBlock_t* b);
// Crea coppie di blocchi e li mescola
extern bool SceneCreatePairsAndShuffle();
// Pulisce i blocchi della scena, liberando la memoria
extern void SceneClearBlocks();
// Inizializza il timer
extern void SceneInitTimer();
extern void SceneEndTimer();
// Ritorna il tempo trascorso dall'inizio del round
extern char* SceneGetTimerText();
// Controlla se tutti i blocchi sono stati completati
extern bool SceneIsRoundWinned();

#endif // !_SCENE_
