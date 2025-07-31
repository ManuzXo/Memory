#include <stdio.h>
#include "args.h"
#include "scene.h"
int main(int argc, char*argv[]) {
	Args_Init(argc, argv);
	SceneInit(2, 2);
	return 0;
}