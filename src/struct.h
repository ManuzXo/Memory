#pragma once
#ifndef _STRUCT_
#define _STRUCT_
#include "raylib/raylib.h"
typedef struct {
	int index;
	int x;
	int y;
	int width;
	int height;
	int number;
	Color color;
	bool done;
}GridBlock_t;
#endif // !_STRUCT_
