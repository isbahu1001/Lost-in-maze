/* gameinfo.c  -  Imaan SAmi
this folder contains game statistics 

HUD, Door Journal, Level Complete and Menu will be added here later.*/

#include <stdio.h>
#include "raylib.h"
#include "gameinfo.h"

// Gobal variable

int seconds = 0; // stored time in seconds
int score = 0; // stores players current score 

double startTime = 0;     // time when the level began 
int timerRunning = 0;     // 1 - clock is ticking, 0 - stopped
int frozenSeconds = 0;    // the time we keep when the clock is stopped


// Starts the clock from the beginning
// Call it when a level begins (NOT inside loadLevel, because the
// fake exit calls loadLevel and we do not want to lose its penalty).
void startTimer()
{
    startTime = GetTime(); // GetTime() is a Raylib function, tells how much time passed since the program started 
    timerRunning = 1;
    time_adjust = 0;
}


// stop the timer when player completes the level
void stopTimer()
{
    frozenSeconds = getSeconds(); // stops the timer while looking at the diplay screen
    timerRunning = 0;
}


//calculates time spent by player on current level
int getSeconds()
{
    int s; // stores calculated time

    if (timerRunning == 0){
        return frozenSeconds;
    }    
    s = (int)(GetTime() - startTime) + time_adjust;

    if (s < 0)      // time can never be negative
       { s = 0;
    }

    seconds = s;
    return s;
}


// converts seconds into readable time format , used in the HUD 
void formatTime(int totalSeconds, char text[])
{
    int mins = totalSeconds / 60;
    int secs = totalSeconds % 60;

    sprintf(text, "%02d:%02d", mins, secs); // converts numbers into formatted text
}


// increment the move counter after every successful movemnt 
void addMove()
{
    moves++;
}


// Score = base + keys*100 - moves*2 - seconds*3
// base is 3000, 6000 or 9000 for level 1, 2, 3
int calcScore()
{
    int base;

    if (level == 1)
        {base = 3000;}
    else if (level == 2)
        {base = 6000;}
    else
        {base = 9000;}

    seconds = getSeconds();
    score = base + (keys * 100) - (moves * 2) - (seconds * 3);

    if (score < 0){   // no negative scores
        score = 0;}

    return score;
}
