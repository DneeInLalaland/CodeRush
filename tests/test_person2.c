//Varakron Vimolgarnjana (68070503452)
// Simple simulation harness (no UI, no question system).
// Builds and runs standalone to sanity-check the core loop.
#include "game/game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    GameState gs;
    initGame(&gs, "Noolee", MODE_SPRINT, D3, 20);

    printf("=== CodeRacer Core Logic Smoke Test ===\n");
    srand((unsigned)time(NULL));

    while(!isRaceOver(&gs)){
        // Simulate player answering (70% correct)
        int r = rand()%100;
        int playerCorrect = (r < 70);
        updateRaceOnPlayerAnswer(&gs, playerCorrect);
        updateAICars(&gs);
        checkFinish(&gs);

        printf("[Q%02d] Player pos=%.1f combo=%d %s | AI:",
               gs.currentQuestionIdx,
               gs.player.position,
               gs.player.combo,
               playerCorrect? "OK":"XX");
        for(int i=0;i<NUM_AI_CARS;++i){
            printf(" %s:%.1f", gs.ai[i].name, gs.ai[i].position);
        }
        printf("\n");
    }

    int score = calculateScore(&gs);
    printf("\n*** RACE FINISHED ***\n");
    printf("Player Rank: %d\n", gs.finalRankPlayer);
    printf("Score: %d\n", score);
    printf("Correct=%d Wrong=%d Distance=%.1f\n",
           gs.player.totalCorrect, gs.player.totalWrong, gs.player.position);

    freeGame(&gs);
    return 0;
}
