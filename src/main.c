#include <stdio.h>
#include "args.h"
#include "render.h"
int main(int argc, char*argv[]) {
	Args_Init(argc, argv);
	RenderInit();
	return 0;
}