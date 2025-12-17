//Warattaya Lekma (Aomsin)
//68070503480

// ui.h - UI Display Functions
#ifndef UI_H //continue reading the code below
#define UI_H //defind UI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Platform-specific
#ifdef _WIN32    //for Windows
    #include <windows.h> //header file of Windows API
    #define CLEAR_SCREEN "cls"    //clear screen command of Windows, put in CLEAR_SCREEN
    #define SLEEP(ms) Sleep(ms) //function Sleep() for stop the program (built-in of Windows)
#else //for Mac/Linux
    #include <unistd.h> //header file of Unix/Linux
    #define CLEAR_SCREEN "clear" //clear screen command of Mac/Linux, put in CLEAR_SCREEN
    #define SLEEP(ms) usleep((ms) * 1000) //function Sleep() for stop the program (built-in of Unix/Linux)
#endif


#include "../game/game.h"        // from Nuree
#include "../data/question.h"    // from Pea


// Core UI Functions
void clearScreen();
void drawLine(int length, char character);
void printCentered(const char* text, int width);
void drawBox(const char* title, int width);

// Display Functions
void displayQuestion(Question* q, int questionNum, int totalQuestions);
void displayGameStats(GameState* game);
void displayLeaderboard();

// Screen Functions
void showHowToPlay();
void showTitleScreen();

#endif
