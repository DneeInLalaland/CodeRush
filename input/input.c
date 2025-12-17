/**
 * @file input.c
 * @brief Input System - Implementation
 * @author Sirapobe Parinyarat (68070503483)
 * @date December 2025
 *
 * Implements input handling functions:
 * - clearInputBuffer(): Clear leftover characters in input buffer
 * - validateChoice(): Validate multiple-choice input (A-D)
 * - getPlayerInput(): Get basic answer input from player
 * - getDetailedInput(): Get answer input with timing and attempt tracking
 * - showMainMenu(): Display and handle main menu input
 * - selectDifficulty(): Handle difficulty selection
 * - showPauseMenu(): Handle pause menu input
 * - getNumberInput(): Safely receive numeric input within a range
 * - confirmAction(): Confirm user action using Y/N
 * - waitForEnter(): Pause program until Enter is pressed
 * - getCharInput(): Get single character input
 * - getSafeInput(): Safely read string input
 * - isEmptyInput(): Check if input string is empty
 * - getPlayerName(): Get and validate player name
 */

#include "input.h"

// Function 1: Clear input buffer
// Prevents issues caused by leftover characters (e.g. extra Enter key)
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function 2: Validate multiple-choice input
// Returns 1 if input is between A and D, otherwise returns 0
int validateChoice(char choice) {
    choice = toupper(choice);
    return (choice >= 'A' && choice <= 'D');
}

// Function 3: Get basic player answer
// Loops until a valid A/B/C/D input is received
char getPlayerInput() {
    char input;
    int valid = 0;
    int attempts = 0;

    while (!valid) {
        printf("Your answer (a/b/c/d): ");
        scanf("%c", &input);
        clearInputBuffer();
        attempts++;

        input = toupper(input);

        if (validateChoice(input)) {
            valid = 1;
            printf(" Input accepted: %c\n", input);
        } else {
            printf("Invalid input! Please enter a, b, c, or d.\n");
            if (attempts >= 3) {
                printf(" Hint: Type only one letter (a-d) and press Enter.\n");
            }
        }
    }
    return input;
}

// Function 4: Get detailed player input
// Tracks answer, number of attempts, and time taken
InputData getDetailedInput() {
    InputData data = {0};

    data.startTime = time(NULL);

    printf("\n  Enter your answer (a/b/c/d)  |\n");

    char input;
    int valid = 0;

    while (!valid) {
        printf("\n> ");
        scanf("%c", &input);
        clearInputBuffer();
        data.attempts++;

        input = toupper(input);

        if (validateChoice(input)) {
            valid = 1;
            data.answer = input;
            data.isValid = 1;
            printf("/ You selected: %c\n", input);
        } else {
            printf("Invalid! Please enter a, b, c, or d only.\n");

            if (data.attempts == 3) {
                printf(" Hint: Type a single letter from a to d\n");
            } else if (data.attempts == 5) {
                printf(" Make sure you're typing a letter, not a number!\n");
            } else if (data.attempts >= 7) {
                printf(" Example: Type 'a' and press Enter\n");
            }
        }
    }

    data.endTime = time(NULL);
    data.timeTaken = (int)difftime(data.endTime, data.startTime);

    if (data.timeTaken >= 5) {
        printf(" Time taken: %d seconds\n", data.timeTaken);
    }

    return data;
}

// Function 5: Display main menu
// Returns user's selected menu option
int showMainMenu() {
    printf("\n ||  CODE RACER  || \n\n");
    printf(" 1. Start Race\n");
    printf(" 2. How to Play\n");
    printf(" 3. Settings\n");
    printf(" 4. View Leaderboard\n");
    printf(" 5. Exit\n\n");

    return getNumberInput(1, 5);
}

// Function 6: Select difficulty level
int selectDifficulty() {
    printf("\n Select Difficulty Level |\n\n");
    printf(" 1. Easy   - Basic C concepts\n");
    printf(" 2. Normal - Standard questions\n");
    printf(" 3. Hard   - Tricky problems\n");
    printf(" 4. Expert - Advanced concepts\n");
    printf(" 5. Master - Only for pros!\n\n");

    return getNumberInput(1, 5);
}

// Function 7: Display pause menu
int showPauseMenu() {
    printf("\n PAUSED \n\n");
    printf(" 1. Resume\n");
    printf(" 2. Restart\n");
    printf(" 3. Main Menu\n");
    printf(" 4. Quit\n\n");

    return getNumberInput(1, 4);
}

// Function 8: Get numeric input within a specific range
// Prevents invalid and out-of-range input
int getNumberInput(int min, int max) {
    int input;
    int valid = 0;
    int attempts = 0;

    while (!valid) {
        printf("Enter your choice (%d-%d): ", min, max);

        if (scanf("%d", &input) != 1) {
            printf("X Invalid input! Please enter a number.\n");
            clearInputBuffer();
            attempts++;
            continue;
        }

        clearInputBuffer();
        attempts++;

        if (input >= min && input <= max) {
            valid = 1;
            printf("/ Selected: %d\n", input);
        } else {
            printf("X Out of range! Please enter a valid option.\n");
        }
    }
    return input;
}

// Function 9: Confirm user action (Yes / No)
int confirmAction(const char* message) {
    printf("! %s\n", message ? message : "Are you sure?");
    printf("(Y/N): ");

    char input;
    while (1) {
        scanf("%c", &input);
        clearInputBuffer();
        input = toupper(input);

        if (input == 'Y') return 1;
        if (input == 'N') return 0;

        printf("Please enter Y or N: ");
    }
}

// Function 10: Wait for Enter key
void waitForEnter() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function 11: Get single character input
char getCharInput() {
    char input;
    scanf(" %c", &input);
    clearInputBuffer();
    return toupper(input);
}
