
#include "player.h"

// Store the player's position
int playerRow = -1;
int playerCol = -1;

// Find the starting position
void InitializePlayer(int rows, int cols, char maze[rows][cols])
{
    playerRow = -1;
    playerCol = -1;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (maze[i][j] == 'S')
            {
                playerRow = i;
                playerCol = j;
                return;
            }
        }
    }
}

// Move the player in the given direction
void MovePlayer(char direction)
{
    if (direction == 'u' || direction == 'U')
    {
        playerRow--;
    }
    else if (direction == 'd' || direction == 'D')
    {
        playerRow++;
    }
    else if (direction == 'l' || direction == 'L')
    {
        playerCol--;
    }
    else if (direction == 'r' || direction == 'R')
    {
        playerCol++;
    }
}

// Check whether the new position is valid
int CheckCollision(int rows, int cols, char maze[rows][cols], int newRow, int newCol)
{
    if (newRow >= 0 && newRow < rows &&
        newCol >= 0 && newCol < cols)
    {
        if (maze[newRow][newCol] == '#')
        {
            return 0; // Movement blocked
        }
        else
        {
            return 1; // Movement allowed
        }
    }

    return 0; // Outside maze boundaries
}
