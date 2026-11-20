
#include "game.h"
#include "maze.h"
#include "player.h"

// Stores whether the player has collected the key
int hasKey = 0;


// Initialize the selected maze
void InitializeSelectedMaze(int currentLevel, int maze3B)
{
    // Reset key status whenever a new maze starts
    hasKey = 0;

    switch (currentLevel)
    {
        case 1:
            InitializePlayer(LEVEL1_ROWS, LEVEL1_COLS, mazeLevel1);
            break;

        case 2:
            InitializePlayer(LEVEL2_ROWS, LEVEL2_COLS, mazeLevel2);
            break;

        case 3:
            if (maze3B == 0)
            {
                InitializePlayer(LEVEL3_ROWS, LEVEL3_COLS, mazeLevel3A);
            }
            else
            {
                InitializePlayer(LEVEL3_ROWS, LEVEL3_COLS, mazeLevel3B);
            }
            break;

        default:
            playerRow = -1;
            playerCol = -1;
            break;
    }
}


// Check collision in the currently selected maze
int CheckCurrentMaze(int currentLevel, int maze3B, int newRow, int newCol)
{
    switch (currentLevel)
    {
        case 1:
            return CheckCollision(
                LEVEL1_ROWS,
                LEVEL1_COLS,
                mazeLevel1,
                newRow,
                newCol
            );

        case 2:
            return CheckCollision(
                LEVEL2_ROWS,
                LEVEL2_COLS,
                mazeLevel2,
                newRow,
                newCol
            );

        case 3:
            if (maze3B == 0)
            {
                return CheckCollision(
                    LEVEL3_ROWS,
                    LEVEL3_COLS,
                    mazeLevel3A,
                    newRow,
                    newCol
                );
            }
            else
            {
                return CheckCollision(
                    LEVEL3_ROWS,
                    LEVEL3_COLS,
                    mazeLevel3B,
                    newRow,
                    newCol
                );
            }

        default:
            return 0;
    }
}


// Check if the player has collected the key
void CheckForKey(int currentLevel, int maze3B)
{
    switch (currentLevel)
    {
        case 1:
            if (mazeLevel1[playerRow][playerCol] == 'K')
            {
                hasKey = 1;
                mazeLevel1[playerRow][playerCol] = '.';
            }
            break;

        case 2:
            if (mazeLevel2[playerRow][playerCol] == 'K')
            {
                hasKey = 1;
                mazeLevel2[playerRow][playerCol] = '.';
            }
            break;

        case 3:
            if (maze3B == 0)
            {
                if (mazeLevel3A[playerRow][playerCol] == 'K')
                {
                    hasKey = 1;
                    mazeLevel3A[playerRow][playerCol] = '.';
                }
            }
            else
            {
                if (mazeLevel3B[playerRow][playerCol] == 'K')
                {
                    hasKey = 1;
                    mazeLevel3B[playerRow][playerCol] = '.';
                }
            }
            break;
    }
}


// Check if the player can complete the current maze
int CheckForExit(int currentLevel, int maze3B)
{
    // Player must collect the key first
    if (hasKey == 0)
    {
        return 0;
    }

    switch (currentLevel)
    {
        case 1:
            if (mazeLevel1[playerRow][playerCol] == 'E')
            {
                return 1;
            }
            break;

        case 2:
            if (mazeLevel2[playerRow][playerCol] == 'E')
            {
                return 1;
            }
            break;

        case 3:
            if (maze3B == 0)
            {
                if (mazeLevel3A[playerRow][playerCol] == 'E')
                {
                    return 1;
                }
            }
            else
            {
                if (mazeLevel3B[playerRow][playerCol] == 'E')
                {
                    return 1;
                }
            }
            break;
    }

    return 0;
}
