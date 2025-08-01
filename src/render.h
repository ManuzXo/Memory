#pragma once
#ifndef _RENDER_
#define _RENDER_
#include <stdbool.h>
#include "struct.h"

// -- GRAPHICS STUFF --
extern unsigned int vRenderMonitor;
extern unsigned int vRenderFps;
extern bool vRenderFullscreen;
extern bool vRenderExit;
extern MouseCursor vRenderMouseCursor;

// -- GAME BLOCK LOGIC STUFF --
extern unsigned int vRenderBlockPickedCount;
extern GridBlock_t* vRenderBlockChoosed[2];
extern bool vRenderStartAnimation;
extern int vRenderTickAnimation;


// -- METHODS --

//Init del render
extern void RenderInit();
//Imposta gli stati per la window
extern void RenderSetWindowState();
//Main Loop
extern void RenderLoop();
extern inline void RenderMainLogic();
//Disegna il testo di avvio
extern void RenderDrawStartAnimation();
//Aggiorna le coordinate e dimensioni dei blocchi in base alla griglia
extern void RenderUpdateBlocksGrids(int maxRow, int maxCol);
//Fa il draw della griglia, ed gridCount è riga e colonna
extern void RenderBlocks();
//Fa il draw di un singolo blocco, con le coordinate del blocco e la sua dimensione
extern void RenderBlock(GridBlock_t* block);
// Seleziona un blocco, aggiungendolo all'array dei blocchi scelti
extern void RenderSelectBlock(GridBlock_t* block);
// Controlla se sono stati scelti due blocchi uguali
extern void RenderCheckResultBlocks();
//Se i blocchi selezionati hanno un numero diverso, inizia l'animazione di ripristino blocchi scelti
extern void RenderCheckAnimationChoosedBlockRestore();
// Ripristina i blocchi scelti, resettando il contatore e le scelte
extern void RenderRestoreChoosedBlocks();
//Controlla se il mouse è sopra un blocco specifico e lo evidenzia, con le coordinate del blocco e la sua dimensione
extern void RenderCheckAndSetMousePointingHand(GridBlock_t* block);
// Controlla se il mouse è sopra un blocco specifico, con le coordinate del blocco e la sua dimensione
extern bool RenderMouseIsHoverBlock(GridBlock_t* block);
//Disegna il numero del blocco, con le coordinate del blocco e la sua dimensione
extern void RenderDrawBlockNumber(GridBlock_t* block);
//Fa il draw di informazioni generali come FPS
extern void RenderInfo();
extern void RenderBtnCallbackGridSize(int maxRow, int maxCol);
//Pulisce il render, chiude la finestra e rilascia le risorse
extern void RenderClear();
#endif // !_RENDER_