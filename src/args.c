#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "args.h"
#include "render.h"

#define ARGS_COUNT (sizeof(ArgsTable) / sizeof(ArgsTable[0]))

void Args_PrintCallback(char* unused) {
	Args_Print();
}
void Args_SetMonitor(char* p1) {
	int value = atoi(p1);
	if (value >= 0)
		vRenderMonitor = value;
	else
		printf("Valore invalido: %s. Non deve essere un integer negativo.\n", p1);
}

void Args_SetFullscreen(char* p1){
	vRenderFullscreen = true;
}

void Args_SetFps(char* p1) {
	int value = atoi(p1);
	if (value > 0)
		vRenderFps = value;
	else
		printf("Valore invalido: %s. Non deve essere un integer negativo o zero.\n", p1);
}

ArgsTable_t ArgsTable[] = {
	 {"-h", "Stampa tutti i comandi disponibili", Args_PrintCallback},
	 {"-m", "Imposta il monitor per raylib 0(primary monitor) 1(secondary monitor) ecc...", Args_SetMonitor},
	 {"-f", "Imposta il monitor a fullscreen", Args_SetFullscreen},
	 {"-fps", "Imposta gli fps per raylib", Args_SetFps},
};

bool Args_Init(int argc, char* argv[]) {
	if (argc == 1) return false;
	bool result = false;
	for (int i = 1; i < ARGS_COUNT; i++) {
		char* argKey = argv[i];
		char* argValue = argv[i + 1];
		if (argKey == NULL) continue;
		for (int j = 0; j < ARGS_COUNT; j++) {
			ArgsTable_t table = ArgsTable[j];
			if (!strcmp(argKey, table.ArgKey)) {
				table.ArgMethod(argValue);
				result = true;
			}
		}
	}
	return result;
}

void Args_Print() {
	for (int i = 0; i < ARGS_COUNT; i++) {
		ArgsTable_t table = ArgsTable[i];
		printf("%s | %s\n", table.ArgKey, table.ArgDesc);
	}
}