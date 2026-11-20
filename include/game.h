
#ifndef GAME_H
#define GAME_H

// Stores whether the player has collected the key
extern int hasKey;

// Initialize the selected maze and player
void InitializeSelectedMaze(int currentLevel, int maze3B);

// Check whether a position is valid
int CheckCurrentMaze(int currentLevel, int maze3B, int newRow, int newCol);

// Check whether the player has collected the key
void CheckForKey(int currentLevel, int maze3B);

// Check whether the player can use the exit
int CheckForExit(int currentLevel, int maze3B);

#endif
