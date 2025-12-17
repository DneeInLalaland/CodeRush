//Warattaya Lekma (Aomsin)
//68070503480

// graphics.c - Graphics Functions
#include "graphics.h" //import header file (function prototypes)
#include "colors.h" //import color
#include "symbols.h" //import symbols
#include "../game/game.h" //GameState struct from previous folder  
#include <string.h>
#include <time.h> //for calculate the time
#include <stdio.h>

//Car
void drawCarSprite(int isPlayer) {
    if (isPlayer) {
        printf("%s", SYM_CAR_PLAYER); //if isPlayer == 1 => car
    } else {
        printf("%s", SYM_CAR_AI); //if isPlayer == 0 => AI
    }
}

//Race Track
void drawRaceTrack(GameState* game) {
    if (!game) return; //if game == NULL => out of this function
    
    clearScreen();
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                    %s CODERUSH - RACE VIEW %s                          ║\n", SYM_FLAG, SYM_FLAG);
    printf("╚════════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    
    int trackWidth = 50; // Set track width to 50 for correct alignment with markers
    
    //Show question information
    int displayQNum = game->currentQuestionIdx + 1;
    if (displayQNum > game->totalQuestions) displayQNum = game->totalQuestions;
    
    printf("%s Question %d / %d | ", SYM_QUESTION, //show current and toal question
           displayQNum, 
           game->totalQuestions);
    
    printf("%s Time: ", SYM_TIMER);
    if (game->startTimeSec > 0) { //check that the game start yet?
        time_t now = time(NULL); //put the current time in "now"
        int elapsed = (int)difftime(now, game->startTimeSec); //calculate played time
        printf("%d seconds\n", elapsed); //show play time
    } else { //if not start yet, show 0 second
        printf("0 seconds\n");
    }
    printf("\n");
    
    //Track header
    printf("START ");
    for (int i = 0; i < trackWidth; i++) {
        printf("─");
    }
    printf(" FINISH\n");
    
    //Player position
    printf("YOU   ");
    int playerPos = (int)((game->player.position * trackWidth) / game->finishLine); //calculate player position (player position * track width / finish line (=100))
    if (playerPos > trackWidth) playerPos = trackWidth; //prevent over position
    
    for (int i = 0; i < trackWidth; i++) { //track width times (50)loop
        if (i == playerPos) {
            printf("%s", COLOR_GREEN); //words in green
            drawCarSprite(1);
            printf("%s", COLOR_RESET); //reset color
        } else if (i % 10 == 0) {
            printf("│"); //marker helping see the distance
        } else {
            printf(" ");
        }
    }
    
    // Show position in percentage
    int playerPercent = (int)((game->player.position / game->finishLine) * 100); //calculate player % => (player position/finish line(=100))*100
    if (playerPercent > 100) playerPercent = 100; //prevent over percentage
    printf(" (%d%%)", playerPercent);
    
    // Show combo
    if (game->player.combo > 0) {
        printf(" %s%s%d%s", COLOR_YELLOW, SYM_COMBO, game->player.combo, COLOR_RESET); //yellow combo number , symbol and then reset color
    }
    printf("\n");
    
    //Show AI position
    for (int i = 0; i < NUM_AI_CARS; i++) { //loop 3 AI
        Racer* ai = &game->ai[i]; //pointer ai point to AI(i)
        printf("%-6s", ai->name); //show "AI", width = 6, "-" make it stay on the left
        
        int aiPos = (int)((ai->position * trackWidth) / game->finishLine); //calculate ai position
        if (aiPos > trackWidth) aiPos = trackWidth; //prevent over position
        
        for (int j = 0; j < trackWidth; j++) {
            if (j == aiPos) {
                printf("%s", COLOR_CYAN); //word in cyan color
                drawCarSprite(0);
                printf("%s", COLOR_RESET); //reset color
            } else if (j % 10 == 0) {
                printf("│"); //marker helping see the distance
            } else {
                printf(" ");
            }
        }
        
        //Show position in percentage (AI)
        int aiPercent = (int)((ai->position / game->finishLine) * 100); //calculate ai % => (ai position/finish line(=100))*100
        if (aiPercent > 100) aiPercent = 100; //prevent over percentage
        printf(" (%d%%)\n", aiPercent);
    }
    
    //Track footer
    printf("      "); // Align with "YOU   " (6 chars)
    for (int i = 0; i <= trackWidth; i++) {
        if (i % 10 == 0) {
            printf("|");
        } else {
            printf("─");
        }
    }
    printf("\n");
    
    //Show markers position
    printf("      "); // Align with "YOU   "
    for (int i = 0; i <= 100; i += 20) {
        if (i == 100) {
            printf("%d", i);
        } else {
            printf("%-10d", i);
        }
    }
    printf("\n\n");
    
    //Show statics
    printf("┌────────────────────────────────────────────────────────────────────┐\n");
    printf("│ %s Stats: ", SYM_STATS); //show static symbol and word
    printf("%s Correct: %d ", SYM_CHECK, game->player.totalCorrect); //show correct symbol, correct answer value and word
    printf("%s Wrong: %d ", SYM_CROSS, game->player.totalWrong); //show wrong symbol, wrong answer value and word
    
    //Calculate accuracy
    int totalAnswered = game->player.totalCorrect + game->player.totalWrong; //correct answers + wrong answers
    float accuracy = 0;
    if (totalAnswered > 0) {
        accuracy = (float)game->player.totalCorrect / totalAnswered * 100; //calculate accuracy => (total correct answer / all answer)*100 
    }
    printf("%s Accuracy: %.1f%% ", SYM_TARGET, accuracy); //show target symbol, accuracy and word
    printf("\n");
    
    printf("└────────────────────────────────────────────────────────────────────┘\n");
    printf("\n");
}
