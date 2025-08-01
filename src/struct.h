#pragma once
#ifndef _STRUCT_
#define _STRUCT_
#include "raylib/raylib.h"

#define BLOCK_COLOR_PICKED LIGHTGRAY
#define BLOCK_COLOE_DONE GREEN
#define BLOCK_COLOR_DEFAULT GRAY

typedef struct {
	int index;
	int x;
	int y;
	int width;
	int height;
	int number;
	Color color;
	bool done;
	bool picked;
}GridBlock_t;


#endif // !_STRUCT_
