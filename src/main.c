#include <stdio.h>
#include "args.h"
#include "scene.h"
#include "render.h"
int main(int argc, char* argv[]) {
	Args_Init(argc, argv);
	if (SceneInit(2, 2)) {
		RenderInit();
		SceneClearBlocks();
	}
	return 0;
}