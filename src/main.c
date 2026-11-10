#include "raylib.h"

int main()
{
    InitWindow(800, 600, "Maze Game");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("My Maze Game", 300, 280, 30, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}