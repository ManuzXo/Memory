#pragma once
#include <stdbool.h>

// -- METHOD --
extern void Args_PrintCallback(char *unused);
extern void Args_SetMonitor(char* p1);

// -- DATA STRUCTURE --
typedef void(*ArgsMethod_t)(char *p1);
typedef struct{
    char *ArgKey;
    char *ArgDesc;
    ArgsMethod_t ArgMethod;
}ArgsTable_t;
extern ArgsTable_t ArgsTable[];

// -- FN --
extern bool Args_Init(int argc, char*argv[]);
extern void Args_Print();