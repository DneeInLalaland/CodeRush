/**
 * @file main.c
 * @brief CodeRush Main Program - Game Integration
 * @author Rinrada Dejsuwannachai (68070503490)
 * @date December 2025
 * 
 * Main entry point that integrates all modules:
 * - Person 1: Question System (Rinrada)
 * - Person 2: Game Logic (Varakron)
 * - Person 3: Input System (Sirapobe)
 * - Person 4: UI Display (Warattaya)
 * - Person 5: Save/Load System (Karnsinee)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// Include all headers
#include "data/question.h"
#include "game/game.h"
#include "input/input.h"
#include "ui/ui.h"
#include "ui/graphics.h"
#include "ui/animation.h"
#include "ui/colors.h"
#include "save/save.h"

// Function prototypes
void displayMainMenu();
void playGame();
void showTutorial();
void showLeaderboard();
int getMenuChoice();

// ========================================
// MAIN FUNCTION
// ========================================

int main() {
    // Seed random number generator
    srand((unsigned int)time(NULL));
    
    // Create save directories
    createDirectories();
    
    // Main menu loop
    while (1) {
        displayMainMenu();
        int choice = getMenuChoice();
        
        switch (choice) {
            case 1:
                playGame();
                break;
            case 2:
                showTutorial();
                break;
            case 3:
                showLeaderboard();
                break;
            case 4:
                clearScreen();
                printf("\n");
                printf("+=======================================================================================+\n");
                printf("|                                                                                       |\n");
                printf("|                      🏁  Thank you for playing CodeRush!  🏁                          |\n");
                printf("|                                                                                       |\n");
                printf("+=======================================================================================+\n");
                printf("\n");
                return 0;
            default:
                printf("\n[X] Invalid choice! Please try again.\n");
                printf("Press Enter to continue...");
                waitForEnter();
                break;
        }
    }
    
    return 0;
}

// ========================================
// MAIN MENU
// ========================================

void displayMainMenu() {
    clearScreen();
    printf("\n\n");
    printf("+=======================================================================================+\n");
    printf("|                                                                                       |\n");
    printf("|                      🏎️  CODE RUSH - RACING GAME  🏎️                                    |\n");
    printf("|                                                                                       |\n");
    printf("|                     Answer C Programming Questions to Race!                           |\n");
    printf("|                                                                                       |\n");
    printf("+=======================================================================================+\n");
    printf("\n");
    printf("+---------------------------------------------------------------------------------------+\n");
    printf("|                                    MAIN MENU                                          |\n");
    printf("+---------------------------------------------------------------------------------------+\n");
    printf("|                                                                                       |\n");
    printf("|          1. 🎮  Start Game                                                            |\n");
    printf("|          2. 📖  How to Play                                                           |\n");
    printf("|          3. 🏆  Leaderboard                                                           |\n");
    printf("|          4. 🚪  Exit                                                                  |\n");
    printf("|                                                                                       |\n");
    printf("+---------------------------------------------------------------------------------------+\n");
    printf("\n");
}

int getMenuChoice() {
    printf("Enter your choice (1-4): ");
    int choice = getNumberInput(1, 4);
    return choice;
}

// ========================================
// PLAY GAME
// ========================================

void playGame() {
    clearScreen();
    
    // Get player name
    printf("\n");
    printf("+======================================================================+\n");
    printf("|                          NEW GAME                                    |\n");
    printf("+======================================================================+\n");
    printf("\n");
    
    char playerName[50];
    printf("Enter your name: ");
    fgets(playerName, sizeof(playerName), stdin);
    playerName[strcspn(playerName, "\n")] = '\0'; // Remove newline
    
    if (strlen(playerName) == 0) {
        strcpy(playerName, "Player");
    }
    
    // Select game mode
    printf("\n");
    printf("Select Game Mode:\n");
    printf("1. Quick Race (10 questions)\n");
    printf("2. Standard Race (15 questions)\n");
    printf("3. Endurance Race (20 questions)\n");
    printf("\nYour choice (1-3): ");
    int modeChoice = getNumberInput(1, 3);
    
    GameMode mode;
    int numQuestions;
    switch (modeChoice) {
        case 1:
            mode = MODE_SPRINT;
            numQuestions = 10;
            break;
        case 2:
            mode = MODE_VS;
            numQuestions = 15;
            break;
        case 3:
            mode = MODE_SURVIVAL;
            numQuestions = 20;
            break;
        default:
            mode = MODE_SPRINT;
            numQuestions = 10;
            break;
    }
    
    // Select difficulty
    printf("\n");
    printf("Select Difficulty:\n");
    printf("1. Easy (*)\n");
    printf("2. Normal (**)\n");
    printf("3. Hard (***)\n");
    printf("4. Expert (****)\n");
    printf("5. Master (*****)\n");
    printf("\nYour choice (1-5): ");
    int diffChoice = getNumberInput(1, 5);
    Difficulty difficulty = (Difficulty)diffChoice;
    
    // Load questions
    QuestionBank* bank = createQuestionBank();
    loadQuestionsFromFile(bank, "data/questions/questions.txt");
    
    if (bank->count == 0) {
        printf("\n[X] Error: No questions loaded! Please check questions.txt\n");
        printf("Press Enter to continue...");
        waitForEnter();
        freeQuestionBank(bank);
        return;
    }
    
    // Initialize game
    GameState game;
    initGame(&game, playerName, mode, difficulty, numQuestions);
    
    // Show countdown
    showCountdown();
    
    // Game loop
    for (int i = 0; i < numQuestions; i++) {
        // Calculate adaptive difficulty
        int currentDiff = calculateAdaptiveDifficulty(difficulty, game.player.combo);
        
        // Show difficulty increase notification
        if (currentDiff > (int)difficulty) {
            printf("\n%s🔥 DIFFICULTY UP! LEVEL %d 🔥%s\n", COLOR_RED, currentDiff, COLOR_RESET);
        }
        
        // Get random question based on adaptive difficulty
        Question* q = getRandomQuestion(bank, currentDiff);
        if (!q) {
            printf("\n[X] Error: Could not get question!\n");
            break;
        }
        
        // Display race track
        drawRaceTrack(&game);
        
        // Display question
        displayQuestion(q, i + 1, numQuestions);
        
        // Get player answer
        printf("\nYour answer (A/B/C/D): ");
        char answer = getCharInput();
        
        // Check answer
        bool correct = checkAnswer(q, answer);
        
        // Show feedback animation
        if (correct) {
            showCorrectAnimation();
            if (game.player.combo >= 3) {
                showComboEffect(game.player.combo);
            }
        } else {
            showWrongAnimation();
        }
        
        // Update game state
        updateRaceOnPlayerAnswer(&game, correct);
        updateAICars(&game);
        checkFinish(&game);
        
        // Check if race is over
        if (isRaceOver(&game)) {
            break;
        }
        
        // Small pause
        printf("\nPress Enter to continue...");
        waitForEnter();
    }
    
    // Show final race track
    drawRaceTrack(&game);
    printf("\nPress Enter to see results...");
    waitForEnter();
    
    // Display final stats
    displayGameStats(&game);
    
    // Save score
    int finalScore = calculateScore(&game);
    saveScore(playerName, finalScore, game.finalRankPlayer, (int)difficulty);
    
    printf("\n[OK] Score saved successfully!\n");
    printf("\nPress Enter to continue...");
    waitForEnter();
    
    // Cleanup
    freeQuestionBank(bank);
    freeGame(&game);
}

// ========================================
// SHOW TUTORIAL
// ========================================

void showTutorial() {
    showHowToPlay();
    printf("\nPress Enter to return to main menu...");
    waitForEnter();
}

// ========================================
// SHOW LEADERBOARD
// ========================================

void showLeaderboard() {
    clearScreen();
    displayTop10();
    printf("\nPress Enter to return to main menu...");
    waitForEnter();
}