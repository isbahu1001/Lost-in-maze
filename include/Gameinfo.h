// gameinfo.h  -  Imaan 
// Game info: timer, move counter, score (HUD, journal and menus will come here too).
// Put this file in the  include  folder.

#ifndef GAMEINFO_H
#define GAMEINFO_H

// ---------- variables made in gameinfo.c (Person B) ----------
extern int seconds;   // time the player has used (with time doors counted)
extern int score;     // score of the current level

// ---------- variables from other files ----------
extern int moves;         // main.c / player.c (Person A)
extern int keys;          // main.c / player.c (Person A)
extern int level;         // main.c (Person A)
extern int time_adjust;   // doors.c (Person B)

// ---------- functions in gameinfo.c ----------
void startTimer();                          // call when a level begins
void stopTimer();                           // call when a level is finished
int  getSeconds();                          // time used so far
void formatTime(int totalSeconds, char text[]);  // makes "01:43" text
void addMove();                             // call after every good move
int  calcScore();                           // works out and returns the score

#endif