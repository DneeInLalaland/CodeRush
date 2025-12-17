//Warattaya Lekma (Aomsin)
//68070503480

// ui.c - Core UI Functions
#include "ui.h" //header (prototype)
#include "colors.h" //import colors
#include "symbols.h" //import symbols
#include "../game/game.h" //GameState struct
#include "../data/question.h" //Question struct
#include <string.h>
#include <time.h> //import time calculation
#include <stdio.h>
#include <stdlib.h>

//=======================
// Clear screen function
void clearScreen() {
    #ifdef _WIN32 //for Windows
        system("cls"); //use this command
    #else //for Mac/Linux 
        system("clear"); //use this command
    #endif
}

//==============
//Draw line
void drawLine(int length, char character) {
    for (int i = 0; i < length; i++) { //to draw character up to the length
        printf("%c", character);
    }
    printf("\n");
}

//=========================================
//Show the message in the middle of screen
void printCentered(const char* text, int width) {
    int padding = (width - (int)strlen(text)) / 2; //space on the left hand
    for (int i = 0; i < padding; i++) { //print space on the left hand
        printf(" ");
    }
    printf("%s\n", text);
}

//================================
//Draw a box => 
/* 
╔══════════════════════════════╗
║         MY TITLE             ║
╠══════════════════════════════╣
*/
void drawBox(const char* title, int width) {
    printf("╔");
    for (int i = 0; i < width - 2; i++) {
        printf("═");
    }
    printf("╗\n");
    
    if (title) {
        printf("║");
        int padding = (width - 2 - (int)strlen(title)) / 2;
        for (int i = 0; i < padding; i++) {
            printf(" ");
        }
        printf("%s", title);
        for (int i = 0; i < (width - 2 - (int)strlen(title) - padding); i++) {
            printf(" ");
        }
        printf("║\n");
        
        printf("╠");
        for (int i = 0; i < width - 2; i++) {
            printf("═");
        }
        printf("╣\n");
    }
}

//===================
// DISPLAY QUESTION


void displayQuestion(Question* q, int questionNum, int totalQuestions) {
    if (!q) return; //if q == NULL, out of this function
    
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════════╗\n");
    printf("║                      %s QUESTION %2d / %2d                           ║\n",
           SYM_QUESTION, questionNum, totalQuestions); //print sysmbols, current question number and total question number
    printf("╠════════════════════════════════════════════════════════════════════╣\n");
    
    //Show the difficulty
    printf("║ Difficulty: ");
    for (int i = 0; i < q->difficulty; i++) { //draw stars up to difficulty level
        printf("%s", SYM_STAR_FULL);
    }
    for (int i = q->difficulty; i < 5; i++) {
        printf("%s", SYM_STAR_EMPTY);    //draw empty star up to 5 - difficulty level star
    }
     printf("\n");
    printf("╠════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                    ║\n");
    
    //Show question
    printf("║ %sQuestion:%s                                                          ║\n", COLOR_CYAN, COLOR_RESET);
    printf("║   ┌────────────────────────────────────────────────────────────┐   ║\n");
    printf("║   │ %s%-58s%s │   ║\n", COLOR_YELLOW, q->question, COLOR_RESET);               //print question in yellow and then reset color
    printf("║   └────────────────────────────────────────────────────────────┘   ║\n");
    printf("║                                                                    ║\n");
    printf("╠════════════════════════════════════════════════════════════════════╣\n");
    printf("║ %sChoose the correct answer:%s                                         ║\n", COLOR_BOLD, COLOR_RESET);      //print bold words
    printf("╠════════════════════════════════════════════════════════════════════╣\n");
    
    //Show choices     

    char choiceLabels[] = {'A', 'B', 'C', 'D'};
    for (int i = 0; i < 4; i++) {
        printf("║                                                                    ║\n");
        printf("║  %s%c)%s %-62s ║\n",
               COLOR_GREEN, choiceLabels[i], COLOR_RESET, q->choices[i]);      //using green color display
    }
    printf("║                                                                    ║\n");
    printf("╚════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
}


// ========================================
// DISPLAY GAME STATS


void displayGameStats(GameState* game) {
    if (!game) return; //if q == NULL, out of this function
    
    clearScreen();
    printf("\n\n");
    printf("╔════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                                                    ║\n");
    printf("║                     %s RACE FINISHED! %s                           ║\n", SYM_FLAG, SYM_FLAG); //print symbols and words
    printf("║                                                                    ║\n");
    printf("╚════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    
    //Show rank
    printf("┌────────────────────────────────────────────────────────────────────┐\n");
    printf("│                         %s FINAL RESULTS                           │\n", SYM_STATS); //print symbols and words
    printf("├────────────────────────────────────────────────────────────────────┤\n");
    printf("│                                                                    │\n");
    
    // Medal based on rank
    const char* medal;
    const char* color;
    if (game->finalRankPlayer == 1) {
        medal = SYM_MEDAL_GOLD;
        color = COLOR_YELLOW;
    } else if (game->finalRankPlayer == 2) {       //set the medal match with color and rank
        medal = SYM_MEDAL_SILVER;
        color = COLOR_WHITE;
    } else if (game->finalRankPlayer == 3) {
        medal = SYM_MEDAL_BRONZE;
        color = COLOR_YELLOW;
    } else {
        medal = "  ";
        color = COLOR_RESET;
    }
    
    printf("│  %s%s Final Rank: #%d / 4%s                                             │\n",    //show final rank of the player
           color, medal, game->finalRankPlayer, COLOR_RESET);
    printf("│  Player: %-30s                            │\n", game->player.name); //show player name
    
    //Show position in percentage
    int playerPercent = (int)((game->player.position / game->finishLine) * 100); //calculate the percentage
    if (playerPercent > 100) playerPercent = 100; //prevent over percentage
        if(playerPercent == 100){
            printf("│  Final Position: %d%%                                              │\n",     //print percentage
           playerPercent);
        }
        else if(playerPercent<10){
            printf("│  Final Position: %d%%                                                │\n",     //print percentage
           playerPercent);
        }
        else{
            printf("│  Final Position: %d%%                                               │\n",     //print percentage
           playerPercent);
            }
    printf("│                                                                    │\n");
    printf("├────────────────────────────────────────────────────────────────────┤\n");
    printf("│                        %s STATISTICS                               │\n", SYM_STATS);                 //print words and symbols
    printf("├────────────────────────────────────────────────────────────────────┤\n");
    printf("│                                                                    │\n");
    printf("│  %s Correct Answers:  %2d                                           │\n",
           SYM_CHECK, game->player.totalCorrect);                                                 //print correct answers
    printf("│  %s Wrong Answers:    %2d                                           │\n",
           SYM_CROSS, game->player.totalWrong);                                                    //print wrong answers
    
    //Accuracy
    int totalAnswered = game->player.totalCorrect + game->player.totalWrong;    //find total awnswer
    float accuracy = 0;
    if (totalAnswered > 0) {
        accuracy = (float)game->player.totalCorrect / totalAnswered * 100;         //calculate accuracy
    }
    if(accuracy == 100.0){
        printf("│  %s Accuracy:         %.1f%%                                     │\n",
           SYM_TARGET, accuracy);
    }
    else if(accuracy >=10.0 && accuracy<100.0){
    printf("│  %s Accuracy:         %.1f%%                                        │\n",
           SYM_TARGET, accuracy);                  
    }
    else{
    printf("│  %s Accuracy:         %.1f%%                                       │\n",
           SYM_TARGET, accuracy);                                                              //print accuracy and symbol
    }
    printf("│                                                                    │\n");
    
    //Time
    if (game->endTimeSec > game->startTimeSec) {
        int timeUsed = (int)(game->endTimeSec - game->startTimeSec);        //played time
        if(timeUsed >=100){
            printf("│  %s  Time Used:        %d seconds                                  │\n",
               SYM_TIMER, timeUsed);   
        }
        else{
            printf("│  %s  Time Used:        %d seconds                                   │\n",
               SYM_TIMER, timeUsed);                                                              //print played time and symbol
        }
    }
    
    printf("│                                                                    │\n");
    printf("├────────────────────────────────────────────────────────────────────┤\n");
    printf("│                       %s AI OPPONENTS                              │\n", SYM_CAR_AI);   //print words and symbol
    printf("├────────────────────────────────────────────────────────────────────┤\n");
    printf("│                                                                    │\n");
    
    //Show AI position
    for (int i = 0; i < NUM_AI_CARS; i++) {    //AI 1, 2, 3
        int aiPercent = (int)((game->ai[i].position / game->finishLine) * 100);         //calculate AI percentage
        if (aiPercent > 100) aiPercent = 100;      //prevent over percentage
        
        printf("│  %d. %-20s Position: %3d%%                            │\n",           //show AI name at the left side and percentage 
               i + 1,
               game->ai[i].name,
               aiPercent);
    }
    
    printf("│                                                                    │\n");
    printf("└────────────────────────────────────────────────────────────────────┘\n");
    printf("\n");
    
    // calculate score
    int score = calculateScore(game);
    printf("┌────────────────────────────────────────────────────────────────────┐\n");
    printf("│                   %s FINAL SCORE: %5d                            │\n", SYM_TARGET, score);     //print words score and symbol
    printf("└────────────────────────────────────────────────────────────────────┘\n");
    printf("\n");
}

//======================
// DISPLAY LEADERBOARD


void displayLeaderboard() {
    clearScreen();
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════════╗\n");
    printf("║                      %s LEADERBOARD %s                             ║\n", SYM_TROPHY, SYM_TROPHY);        //show symbol and words
    printf("╚════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("┌──────┬────────────────────────┬─────────┬────────┬──────────────┐\n");
    printf("│ Rank │ Player Name            │ Score   │ Rank   │ Date         │\n");
    printf("├──────┼────────────────────────┼─────────┼────────┼──────────────┤\n");
    
    // example information for check running correctly
    printf("│  %s  │ CodeMaster             │  15420  │   1    │  2025-11-04  │\n", SYM_MEDAL_GOLD);
    printf("│  %s  │ SpeedCoder             │  13890  │   2    │  2025-11-03  │\n", SYM_MEDAL_SILVER);
    printf("│  %s  │ ByteWarrior            │  12350  │   1    │  2025-11-02  │\n", SYM_MEDAL_BRONZE);
    printf("│   4  │ AlgoNinja              │  11200  │   3    │  2025-11-01  │\n");
    printf("│   5  │ SyntaxKing             │  10450  │   2    │  2025-10-31  │\n");                               
    
    printf("└──────┴────────────────────────┴─────────┴────────┴──────────────┘\n");
    printf("\n");
    printf("Press Enter to continue...");
    getchar();
}

//==================
// SCREEN FUNCTIONS


void showHowToPlay() {
    clearScreen();
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════════╗\n");
    printf("║                      %s HOW TO PLAY %s                             ║\n", SYM_BOOK, SYM_BOOK);
    printf("╚════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("┌────────────────────────────────────────────────────────────────────┐\n");
    printf("│                                                                    │\n");
    printf("│  %s GAME OBJECTIVE:                                                │\n", SYM_PLAY);
    printf("│     Race against 3 AI opponents by answering C programming         │\n");
    printf("│     questions correctly. First to reach the finish line wins!      │\n");
    printf("│                                                                    │\n");
    printf("│  %s HOW TO ANSWER:                                                 │\n", SYM_QUESTION);
    printf("│     1. Read the C programming question carefully                   │\n");
    printf("│     2. Choose your answer (A, B, C, or D)                          │\n");
    printf("│     3. Press Enter to submit                                       │\n");
    printf("│                                                                    │\n");
    printf("│  %s COMBO SYSTEM:                                                  │\n", SYM_LIGHTNING);
    printf("│     %s 3+ correct answers: Speed Boost!                            │\n", SYM_FIRE);
    printf("│     %s 5+ correct answers: Super Speed!                            │\n", SYM_FIRE);
    printf("│     %s 7+ correct answers: MEGA SPEED!                             │\n", SYM_LIGHTNING);
    printf("│     %s Wrong answer = Combo reset                                  │\n", SYM_CROSS);
    printf("│                                                                    │\n");
    printf("│  %s SCORING:                                                       │\n", SYM_TROPHY);
    printf("│     %s Correct answers give points                                 │\n", SYM_CHECK);
    printf("│     %s Higher combo = More points                                  │\n", SYM_STAR_FULL);
    printf("│     %s Finishing position matters                                  │\n", SYM_FLAG);               //show symbol and words
    printf("│                                                                    │\n");
    printf("└────────────────────────────────────────────────────────────────────┘\n");
    printf("\n");
}
