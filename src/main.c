#include <stdio.h>
#include "args.h"
#include "scene.h"
#include "render.h"
int main(int argc, char*argv[]) {
	Args_Init(argc, argv);
	SceneInit(4, 4);
	RenderInit();
	SceneClearBlocks();
	return 0;
}