#ifndef _RENDER_
#define _RENDER_
#include <stdbool.h>
extern unsigned int vRenderMonitor;
extern unsigned int vRenderFps;
extern bool vRenderFullscreen;
extern void RenderInit();
extern void RenderSetWindowState();
extern void RenderLoop();
extern void RenderInfo();
extern void RenderClear();
#endif // !_RENDER_