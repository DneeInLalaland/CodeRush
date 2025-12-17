//Warattaya Lekma (68070503480)
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "game/game.h"

// Mock implementation of game.c dependencies if needed, 
// but we are linking against game.o so we should be fine.

void test_sprint_mode() {
    GameState gs;
    initGame(&gs, "TestPlayer", MODE_SPRINT, D1, 10);
    
    printf("Testing Sprint Mode (10 questions)...\n");
    printf("Base Move: %.2f\n", gs.baseMove);
    
    // Simulate 10 correct answers
    for (int i = 0; i < 10; i++) {
        updateRaceOnPlayerAnswer(&gs, true);
    }
    
    printf("Final Position: %.2f / %.2f\n", gs.player.position, gs.finishLine);
    
    // With combo bonuses, position should be > 1000
    if (gs.player.position >= gs.finishLine) {
        printf("Sprint Mode: PASSED\n");
    } else {
        printf("Sprint Mode: FAILED\n");
    }
}

void test_vs_mode() {
    GameState gs;
    initGame(&gs, "TestPlayer", MODE_VS, D1, 15);
    
    printf("\nTesting VS Mode (15 questions)...\n");
    printf("Base Move: %.2f\n", gs.baseMove);
    
    for (int i = 0; i < 15; i++) {
        updateRaceOnPlayerAnswer(&gs, true);
    }
    
    printf("Final Position: %.2f / %.2f\n", gs.player.position, gs.finishLine);
    
    if (gs.player.position >= gs.finishLine) {
        printf("VS Mode: PASSED\n");
    } else {
        printf("VS Mode: FAILED\n");
    }
}

void test_survival_mode() {
    GameState gs;
    initGame(&gs, "TestPlayer", MODE_SURVIVAL, D1, 20);
    
    printf("\nTesting Survival Mode (20 questions)...\n");
    printf("Base Move: %.2f\n", gs.baseMove);
    
    for (int i = 0; i < 20; i++) {
        updateRaceOnPlayerAnswer(&gs, true);
    }
    
    printf("Final Position: %.2f / %.2f\n", gs.player.position, gs.finishLine);
    
    if (gs.player.position >= gs.finishLine) {
        printf("Survival Mode: PASSED\n");
    } else {
        printf("Survival Mode: FAILED\n");
    }
}

int main() {
    test_sprint_mode();
    test_vs_mode();
    test_survival_mode();
    return 0;
}
