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
//Aggiorna le coordinate e dimensioni dei blocchi in base alla griglia
extern void RenderUpdateBlocksGrids(int maxRow, int maxCol);
//Fa il draw della griglia, ed gridCount è riga e colonna
extern void RenderBlocks();
//Fa il draw di un singolo blocco, con le coordinate del blocco e la sua dimensione
extern void RenderBlock(GridBlock_t* block);
// Controlla se il mouse è sopra un blocco specifico, con le coordinate del blocco e la sua dimensione
extern bool RenderMouseIsHoverBlock(GridBlock_t* block);
//Disegna il numero del blocco, con le coordinate del blocco e la sua dimensione
extern void RenderDrawBlockNumber(GridBlock_t* block);
//Fa il draw di informazioni generali come FPS
extern void RenderInfo();
//Pulisce il render, chiude la finestra e rilascia le risorse
extern void RenderClear();
#endif // !_RENDER_