#include <stdlib.h>
#include <string.h>
#include "doors.h"

//These are the global variables that are defined here (declared in doors.h) 

int time_adjust = 0;        // add or substract extra seconds from timer (used in time doors and fake exit)
int fake_exit_hit = 0;       // 0- fake exit not triggered 1- fake exit triggered (player stepped in it)
char doorMessage[60] = ""; // small text drawHUD() can show

/* Wall door - some walls will disappear 
colour is blue 
Format: blue door (B or b) where B- First Endpoint (Dark blue) b- Second endpoint (Light Blue)
which level, row, col (start from 0)*/

int totalWallEntries = 2;
char wallSym[]   = {'b', 'B'}; 
int  wallLevel[] = {1,   1}; // two entries and both belong to level 1 


// wallRow[] and wallCol stores coordinates of position of walls what will disappear
int  wallRow[]   = {8,   8};
int  wallCol[]   = {2,   5};


// mark a door and update the journal
void markFound(int which)
{
    doorFound[which] = 1;
}

//--------LEVEL 1 ( The Tutorial ) Doors ----------
// Return door function send the player back to the starting cooridinates
void returnDoor()
{
    playerRow = startRow;
    playerCol = startCol;
    markFound(RETURN_D);
    strcpy(doorMessage, "Return door! Back to start");
}


/* Teleport door
 Format : (purple dors) T - first end point ( Dark purple ) t - second end point (Light purple) 
 If a maze has more than one pair, the 1st T goes with the 1st t,
the 2nd T with the 2nd t, and so on (counting row by row).*/


void teleportDoor(char symbol) // symbols tells which door player is standing on
{
    int r, c; // r-row c-column
    int myNumber = 0;   // stores number teleport door currently standing on 
    int count = 0; // counts number of matching doors found so far
    char other; // stores the opposite symbol 

    if (symbol == 'T')
        other = 't';
    else
        other = 'T';

    // step 1: find out which number the door we stand on is
    for (r = 0; r < size; r++)
    {
        for (c = 0; c < size; c++)
        {
            if (maze[r][c] == symbol)
            {
                if (r == playerRow && c == playerCol)
                {
                    myNumber = count;
                }
                count++;
            }
        }
    }

    // step 2: go to the door with the same number of the other kind
    count = 0;
    for (r = 0; r < size; r++)
    {
        for (c = 0; c < size; c++)
        {
            if (maze[r][c] == other)
            {
                if (count == myNumber)
                {
                    playerRow = r;
                    playerCol = c;
                    markFound(TELEPORT_D);
                    strcpy(doorMessage, "Teleported!");
                    return;
                }
                count++;
            }
        }
    }
}


// Wall door fuction removes some walls from the maze
void wallDoor(char symbol)
{
    int i;

    for (i = 0; i < totalWallEntries; i++)
    {
        if (wallSym[i] == symbol && wallLevel[i] == level)
        {
            maze[wallRow[i]][wallCol[i]] = '.';
        }
    }
    markFound(WALL_D);
    strcpy(doorMessage, "Some walls disappeared!");
}

/*--------LEVEL 2 ( The Trick) Doors ----------
 One way door: movePlayer() should call this BEFORE moving onto a tile.

dr= direction row  
dc = direction column


 the final direction (after fixDirection). Returns 1 if allowed.*/
int canEnterOneWay(char tile, int dr, int dc)
{
    if (tile == '>' && dc != 1)  return 0; // check whether door facing right
    if (tile == '<' && dc != -1) return 0; // same explaination but for door facing left
    if (tile == '^' && dr != -1) return 0; // door facing up
    if (tile == 'v' && dr != 1)  return 0; // door facing down
    return 1;
}


// Reverse door  flips the controls (stepping on it again fixes them)
void reverseDoor()
{
    /*reverse=0 controls normal, reverse=1 controls reversed*/
    if (reversed == 0)
    {
        reversed = 1;
        strcpy(doorMessage, "Controls reversed!");
    }
    else
    {
        reversed = 0;
        strcpy(doorMessage, "Controls back to normal");
    }
    markFound(REVERSE_D);
}


// movePlayer() should use this on dr and dc so the reverse works
int fixDirection(int d)
{
    if (reversed == 1)
        return -d;
    return d;
}


// Mirror door: flips the whole maze left <-> right
void mirrorDoor()
{
    int r, c, i;
    char temp;

    for (r = 0; r < size; r++)
    {

        /*we only swap half the maze column Because we swap 
        the left side with the right side. If we swapped every column, we would undo the changes.*/
        for (c = 0; c < size / 2; c++) 
        {
            temp = maze[r][c];
            maze[r][c] = maze[r][size - 1 - c];
            maze[r][size - 1 - c] = temp;
        }
    }

    // one-way doors must turn around too
    for (r = 0; r < size; r++)
    {
        for (c = 0; c < size; c++)
        {
            if (maze[r][c] == '>')
                maze[r][c] = '<';
            else if (maze[r][c] == '<')
                maze[r][c] = '>';
        }
    }

    // coordinates of the wall in wall door to be also mirrored that are supposed to be removed
    playerCol = size - 1 - playerCol;
    startCol = size - 1 - startCol;
    for (i = 0; i < totalWallEntries; i++) // totalWallEntries- stores number of walls to be diappered 
    {
        if (wallLevel[i] == level){
            wallCol[i] = size - 1 - wallCol[i];
        }
    }

    markFound(MIRROR_D);
    strcpy(doorMessage, "The maze flipped!");
}




/*--------LEVEL 3 (The Chaos  Doors) ----------*/

// Time door randomly adds or subtracts 10 seconds
// (needs srand(time(NULL)) once in main, and getSeconds() should
//  add timeAdjust and never go below 0)
void timeDoor()
{
    // 0- adds 1- substracts
    if (rand() % 2 == 0)
    {
        time_adjust = time_adjust + 10;
        strcpy(doorMessage, "Time door: +10 seconds");
    }
    else
    {
        time_adjust = time_adjust - 10;
        strcpy(doorMessage, "Time door: -10 seconds");
    }
    markFound(TIME_D);
}


// Invisible door looks like floor but secretly does another door's job
void invisibleDoor()
{
    int pick = rand() % 3;

    if (pick == 0){
        /*returnDoor() functionality is used here instead of  directly calling
         the function because it make use of extra effects */

        playerRow = startRow;
        playerCol = startCol;}
    else if (pick == 1)
        reverseDoor();
    else
        timeDoor();

    markFound(INVISIBLE_D);
    maze[playerRow][playerCol] = '.';   // it vanishes after one use
}


// Fake exit looks like the exit but gives a penalty and changes the maze.
// loadLevel() in main.c should load the "after fake exit" maze when
// fakeExitHit == 1.
void fakeExitDoor()
{
    time_adjust = time_adjust + 20;
    fake_exit_hit = 1;
    markFound(FAKE_D);
    loadLevel(level);
    strcpy(doorMessage, "Fake exit! +20 seconds");
}


// main function that connects the maze symbol to their corresponding functions
void handleDoor(char symbol)
{
    switch (symbol)
    {
        case 'Y':
            returnDoor();
            break;
        case 'T':
        case 't':
            teleportDoor(symbol);
            break;
        case 'B':
        case 'b':
            wallDoor(symbol);
            break;
        case '>':
        case '<':
        case '^':
        case 'v':
            markFound(ONEWAY_D);
            break;
        case 'R':
            reverseDoor();
            break;
        case 'M':
            mirrorDoor();
            break;
        case 'I':
            timeDoor();
            break;
        case 'X':
            invisibleDoor();
            break;
        case 'F':
            fakeExitDoor();
            break;
    }
}