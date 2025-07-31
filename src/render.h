#pragma once
#ifndef _RENDER_
#define _RENDER_
#include <stdbool.h>
extern unsigned int vRenderMonitor;
extern unsigned int vRenderFps;
extern bool vRenderFullscreen;
//Init del render
extern void RenderInit();
//Imposta gli stati per la window
extern void RenderSetWindowState();
//Main Loop
extern void RenderLoop();
//Fa il draw della griglia, ed gridCount è riga e colonna
extern void RenderGrids(int maxRow, int maxCol);
//Fa il draw di informazioni generali come FPS
extern void RenderInfo();
//Pulisce il render, chiude la finestra e rilascia le risorse
extern void RenderClear();
#endif // !_RENDER_