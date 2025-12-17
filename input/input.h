/**
 * @file input.h
 * @brief Input System - Data structures and function declarations
 * @author Sirapobe Parinyarat (68070503483)
 * @date December 2025
 *
 * This module handles all user input interactions for the CodeRush game.
 * It provides input validation, menu navigation, confirmation handling,
 * and detailed input tracking such as attempts and response time.
 */

#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// Platform-specific headers
#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <unistd.h>
    #include <termios.h>
#endif

// Structure for detailed player input
typedef struct {
    char answer;       // Player's selected answer (a/b/c/d)
    int isValid;       // Input validity (1 = valid, 0 = invalid)
    int attempts;      // Number of attempts made by player
    time_t startTime;  // Time when input starts
    time_t endTime;    // Time when input ends
    int timeTaken;     // Time spent answering (seconds)
} InputData;

// Core input utility functions
void clearInputBuffer();          // Clear leftover characters in input buffer
int validateChoice(char choice);  // Validate multiple-choice input (a-d)
char getPlayerInput();            // Get basic player answer
InputData getDetailedInput();     // Get answer with timing and attempts info

// Menu-related input functions
int showMainMenu();               // Display main menu and get selection
int selectDifficulty();           // Display difficulty menu and get selection
int showPauseMenu();              // Display pause menu and get selection

// Confirmation function
int confirmAction(const char* message); // Ask user to confirm an action (Y/N)

// General helper input functions
void waitForEnter();              // Pause program until Enter is pressed
char getCharInput();              // Get single character input
int getNumberInput(int min, int max); // Get numeric input within a range

#endif // INPUT_H
