// doors.h  -  Imaan Sami

#ifndef DOORS_H
#define DOORS_H

#define MAXSIZE 21 // maximum grid size is 21x21

// door numbers for the doorFound[9] array (Door Journal uses this later)
//doorFound[9] keeps track of doors that are found while playing the game

#define RETURN_D    0
#define TELEPORT_D  1
#define WALL_D      2
#define ONEWAY_D    3
#define REVERSE_D   4
#define MIRROR_D    5
#define TIME_D      6
#define INVISIBLE_D 7
#define FAKE_D      8

// variables declared in main.c
extern char maze[MAXSIZE][MAXSIZE];
extern int size;
extern int level;
extern int playerRow, playerCol;
extern int startRow, startCol;
extern int reversed;
extern int doorFound[9];

// variables declared in doors.c (Person B) 
extern int time_adjust;        
extern int fake_exit_hit;      
extern char doorMessage[60];  

// function from main.c that we call 
void loadLevel(int lvl);

//functions in doors.c 
void markFound(int which);
void returnDoor();
void teleportDoor(char symbol);
void wallDoor(char symbol);
int  canEnterOneWay(char tile, int dr, int dc);
void reverseDoor();
int  fixDirection(int d);
void mirrorDoor();
void timeDoor();
void invisibleDoor();
void fakeExitDoor();
void handleDoor(char symbol);

#endif