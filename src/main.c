
#include "raylib.h"
#include "maze.h"
#include "player.h"
#include "game.h"

// Window settings
#define CELL_SIZE 35
#define OFFSET_X 40
#define OFFSET_Y 40


// Function to draw the astronaut player
void DrawPlayer()
{
    int x = OFFSET_X + playerCol * CELL_SIZE + CELL_SIZE / 2;
    int y = OFFSET_Y + playerRow * CELL_SIZE + CELL_SIZE / 2;

    // Backpack
    DrawRectangle(x - 10, y - 2, 5, 10, GRAY);

    // Astronaut body
    DrawRectangleRounded(
        (Rectangle){x - 6, y, 12, 12},
        0.3, 5, LIGHTGRAY
    );

    // Helmet
    DrawCircle(x, y - 5, 9, WHITE);

    // Helmet glass
    DrawEllipse(x, y - 5, 6, 5, SKYBLUE);

    // Visor reflection
    DrawCircle(x - 2, y - 7, 2, WHITE);

    // Boots
    DrawRectangle(x - 5, y + 10, 4, 3, DARKGRAY);
    DrawRectangle(x + 1, y + 10, 4, 3, DARKGRAY);
}


// Function to draw a maze
void DrawMaze(int rows, int cols, char maze[rows][cols])
{
    Color cellColor;

    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            // Assign color according to maze character
            switch (maze[row][col])
            {
                case '#':
                    cellColor = BLACK;
                    break;

                case '.':
                    cellColor = RAYWHITE;
                    break;

                case 'S':
                    cellColor = DARKGREEN;
                    break;

                case 'E':
                    cellColor = GOLD;
                    break;

                case 'R':
                    cellColor = PINK;
                    break;

                case 'M':
                    cellColor = LIME;
                    break;

                case 'K':
                    cellColor = ORANGE;
                    break;

                case 'Y':
                    cellColor = YELLOW;
                    break;

                case 'B':
                case 'b':
                    cellColor = BLUE;
                    break;

                case 'T':
                case 't':
                    cellColor = PURPLE;
                    break;

                case 'G':
                    cellColor = GRAY;
                    break;

                case 'C':
                    cellColor = SKYBLUE;
                    break;

                case 'F':
                    cellColor = RED;
                    break;

                case '>':
                case '<':
                case '^':
                case 'v':
                    cellColor = PINK;
                    break;

                default:
                    cellColor = RAYWHITE;
                    break;
            }

            // Draw the maze cell
            DrawRectangle(
                OFFSET_X + col * CELL_SIZE,
                OFFSET_Y + row * CELL_SIZE,
                CELL_SIZE,
                CELL_SIZE,
                cellColor
            );

            // Draw cell boundaries
            DrawRectangleLines(
                OFFSET_X + col * CELL_SIZE,
                OFFSET_Y + row * CELL_SIZE,
                CELL_SIZE,
                CELL_SIZE,
                LIGHTGRAY
            );
        }
    }
}


// Function to draw the currently selected maze
void DrawSelectedMaze(int currentLevel, int maze3B)
{
    switch (currentLevel)
    {
        case 1:
            DrawMaze(LEVEL1_ROWS, LEVEL1_COLS, mazeLevel1);
            break;

        case 2:
            DrawMaze(LEVEL2_ROWS, LEVEL2_COLS, mazeLevel2);
            break;

        case 3:
            if (maze3B == 0)
            {
                DrawMaze(LEVEL3_ROWS, LEVEL3_COLS, mazeLevel3A);
            }
            else
            {
                DrawMaze(LEVEL3_ROWS, LEVEL3_COLS, mazeLevel3B);
            }
            break;
    }
}


int main()
{
    // Current game level
    int currentLevel = 1;

    // 0 = Level 3A
    // 1 = Level 3B
    int maze3B = 0;

    // Check whether the entire game is completed
    int gameWon = 0;

    // Create Raylib window
    InitWindow(900, 850, "Lost in the Maze");

    SetTargetFPS(60);

    // Initialize player at the starting position
    InitializeSelectedMaze(currentLevel, maze3B);


    // Main game loop
    while (!WindowShouldClose())
    {
        // Detect player movement only if the game is not completed
        char direction = '\0';

        if (!gameWon)
        {
            if (IsKeyPressed(KEY_UP))
            {
                direction = 'u';
            }
            else if (IsKeyPressed(KEY_DOWN))
            {
                direction = 'd';
            }
            else if (IsKeyPressed(KEY_LEFT))
            {
                direction = 'l';
            }
            else if (IsKeyPressed(KEY_RIGHT))
            {
                direction = 'r';
            }
        }


        // Move player and check collision
        if (direction != '\0')
        {
            int oldRow = playerRow;
            int oldCol = playerCol;

            MovePlayer(direction);

            // Check whether the new position is valid
            if (!CheckCurrentMaze(
                currentLevel,
                maze3B,
                playerRow,
                playerCol))
            {
                // Restore the old position if movement is blocked
                playerRow = oldRow;
                playerCol = oldCol;
            }

            // Check whether the player collected the key
            CheckForKey(currentLevel, maze3B);

            // Check whether the player reached the exit with the key
            if (CheckForExit(currentLevel, maze3B))
            {
                if (currentLevel == 1)
                {
                    // Unlock and start Level 2
                    currentLevel = 2;
                    InitializeSelectedMaze(currentLevel, maze3B);
                }
                else if (currentLevel == 2)
                {
                    // Unlock and start Level 3A
                    currentLevel = 3;
                    maze3B = 0;
                    InitializeSelectedMaze(currentLevel, maze3B);
                }
                else if (currentLevel == 3 && maze3B == 0)
                {
                    // Move from Level 3A to Level 3B
                    maze3B = 1;
                    InitializeSelectedMaze(currentLevel, maze3B);
                }
                else if (currentLevel == 3 && maze3B == 1)
                {
                    // Final maze completed
                    gameWon = 1;
                }
            }
        }


        // Begin drawing
        BeginDrawing();

        ClearBackground(RAYWHITE);


        // Display current level
        if (currentLevel == 3)
        {
            if (maze3B == 0)
            {
                DrawText("LEVEL 3A", OFFSET_X, 10, 20, DARKGRAY);
            }
            else
            {
                DrawText("LEVEL 3B", OFFSET_X, 10, 20, DARKGRAY);
            }
        }
        else
        {
            DrawText(
                TextFormat("LEVEL %d", currentLevel),
                OFFSET_X,
                10,
                20,
                DARKGRAY
            );
        }


        // Display key status
        if (hasKey == 1)
        {
            DrawText("KEY: COLLECTED", 200, 10, 20, DARKGREEN);
        }
        else
        {
            DrawText("KEY: NOT COLLECTED", 200, 10, 20, DARKGRAY);
        }


        // Draw selected maze
        DrawSelectedMaze(currentLevel, maze3B);

        // Draw astronaut if position is valid
        if (playerRow >= 0 && playerCol >= 0)
        {
            DrawPlayer();
        }


        // Display game completion message
        if (gameWon)
        {
            DrawRectangle(200, 350, 500, 100, DARKGREEN);

            DrawText(
                "YOU COMPLETED THE MAZE!",
                245,
                385,
                25,
                WHITE
            );
        }


        // End drawing
        EndDrawing();
    }


    // Close Raylib window
    CloseWindow();

    return 0;
}
