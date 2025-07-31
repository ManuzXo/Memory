#include <stdio.h>
#include "raylib/raylib.h"
int main(){
     InitWindow(800, 450, "Basic Window");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Testo di base", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}