#include <stdio.h>
#include <assert.h>
#include "game/game.h"

int main() {
    printf("=== Testing Adaptive Difficulty ===\n");

    // Test 1: Base Difficulty 1 (Easy)
    printf("Test 1: Base Difficulty 1 (Easy)\n");
    assert(calculateAdaptiveDifficulty(D1, 0) == 1); // Combo 0 -> Level 1
    assert(calculateAdaptiveDifficulty(D1, 2) == 1); // Combo 2 -> Level 1
    assert(calculateAdaptiveDifficulty(D1, 3) == 2); // Combo 3 -> Level 2 (+1)
    assert(calculateAdaptiveDifficulty(D1, 5) == 2); // Combo 5 -> Level 2
    assert(calculateAdaptiveDifficulty(D1, 6) == 3); // Combo 6 -> Level 3 (+2)
    printf("PASSED\n");

    // Test 2: Base Difficulty 3 (Hard)
    printf("Test 2: Base Difficulty 3 (Hard)\n");
    assert(calculateAdaptiveDifficulty(D3, 0) == 3); // Combo 0 -> Level 3
    assert(calculateAdaptiveDifficulty(D3, 3) == 4); // Combo 3 -> Level 4
    assert(calculateAdaptiveDifficulty(D3, 6) == 5); // Combo 6 -> Level 5
    assert(calculateAdaptiveDifficulty(D3, 9) == 5); // Combo 9 -> Level 5 (Max Cap)
    printf("PASSED\n");

    // Test 3: Base Difficulty 5 (Master)
    printf("Test 3: Base Difficulty 5 (Master)\n");
    assert(calculateAdaptiveDifficulty(D5, 0) == 5); // Combo 0 -> Level 5
    assert(calculateAdaptiveDifficulty(D5, 10) == 5); // Combo 10 -> Level 5 (Max Cap)
    printf("PASSED\n");

    printf("\nAll adaptive difficulty tests passed!\n");
    return 0;
}
