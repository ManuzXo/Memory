#pragma once
#ifndef _RENDER_
#define _RENDER_
#include <stdbool.h>
#include "struct.h"

extern unsigned int vRenderMonitor;
extern unsigned int vRenderFps;
extern bool vRenderFullscreen;
extern bool vRenderExit;
extern MouseCursor vRenderMouseCursor;
//Init del render
extern void RenderInit();
//Imposta gli stati per la window
extern void RenderSetWindowState();
//Main Loop
extern void RenderLoop();
//Fa il draw della griglia, ed gridCount è riga e colonna
extern void RenderGrids(int maxRow, int maxCol);
//Fa il draw di un singolo blocco, con le coordinate del blocco e la sua dimensione
extern void RenderBlock(int blockNumber, int xBlock, int yBlock, int blockWidth, int blockHeight);
// Controlla se il mouse è sopra un blocco specifico, con le coordinate del blocco e la sua dimensione
extern bool RenderMouseIsHoverBlock(int xBlock, int yBlock, int blockWidth, int blockHeight);
extern void RenderDrawBlockNumber(int blockNumber, int xBlock, int yBlock, int blockWidth, int blockHeight);
//Fa il draw di informazioni generali come FPS
extern void RenderInfo();
//Pulisce il render, chiude la finestra e rilascia le risorse
extern void RenderClear();
#endif // !_RENDER_