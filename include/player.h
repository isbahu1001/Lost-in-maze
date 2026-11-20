#ifndef PLAYER_H
#define PLAYER_H

extern int playerRow;
extern int playerCol;

void InitializePlayer(int rows, int cols, char maze[rows][cols]);
void MovePlayer(char direction);
int CheckCollision(int rows, int cols, char maze[rows][cols], int newRow, int newCol);

#endif