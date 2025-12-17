#include "save/save.h" 
#include <stdio.h> 
 
void test_create_directories() { 
    printf("\n=== Test 1: Create Directories ===\n"); 
     
    int result = createDirectories(); 
     
    if (result) { 
        printf(" ✅ PASS: Directories created/verified\n"); 
    } else { 
        printf(" ❌ FAIL: Cannot create directories\n"); 
    } 
} 
 
void test_save_score() { 
    printf("\n=== Test 2: Save Score ===\n"); 
     
    int result = saveScore("TestPlayer", 5000, 1, 3); 
     
    if (result) { 
        printf(" ✅ PASS: Score saved successfully\n"); 
    } else { 
        printf(" ❌ FAIL: Cannot save score\n"); 
    } 
} 
 
void test_load_leaderboard() { 
    printf("\n=== Test 3: Load Leaderboard ===\n"); 
     
    int count; 
    LeaderboardEntry* entries = loadLeaderboard(&count); 
     
    if (entries && count > 0) { 
        printf(" ✅ PASS: Leaderboard loaded (%d entries)\n", count); 
         
        printf("\nTop 5:\n"); 
        for (int i = 0; i < 5 && i < count; i++) { 
            printf("   %d. %s - %d points (Rank %d)\n", 
                   i + 1, 
                   entries[i].name, 
                   entries[i].score, 
                   entries[i].rank); 
        } 
         
        free(entries); 
    } else { 
        printf(" ⚠  WARNING: No leaderboard data (this is OK for first run)\n"); 
    } 
} 
 
void test_save_player_data() { 
    printf("\n=== Test 4: Save Player Data ===\n"); 
     
    PlayerData data; 
    strcpy(data.name, "TestPlayer"); 
    data.totalGames = 5; 
    data.wins = 2; 
    data.totalScore = 25000; 
    data.bestScore = 6000; 
    data.totalCorrect = 45; 
    data.totalWrong = 5; 
    data.longestCombo = 8; 
    data.lastPlayed = time(NULL); 
     
    int result = savePlayerData(&data); 
     
    if (result) { 
        printf(" ✅ PASS: Player data saved\n"); 
    } else { 
        printf(" ❌ FAIL: Cannot save player data\n"); 
    } 
} 
 
void test_load_player_data() { 
    printf("\n=== Test 5: Load Player Data ===\n"); 
     
    PlayerData* data = loadPlayerData("TestPlayer"); 
     
    if (data) { 
        printf(" ✅ PASS: Player data loaded\n"); 
        printf("   Name: %s\n", data->name); 
        printf("   Total games: %d\n", data->totalGames); 
        printf("   Wins: %d\n", data->wins); 
        printf("   Best score: %d\n", data->bestScore); 
         
        free(data); 
    } else { 
        printf(" ⚠  WARNING: No player data found\n"); 
    } 
} 
 
void test_update_stats() { 
    printf("\n=== Test 6: Update Player Stats ===\n"); 
     
    int result = updatePlayerStats("TestPlayer", 5500, 1, 9, 1, 7); 
     
    if (result) { 
        printf(" ✅ PASS: Stats updated\n"); 
         
        // Load and verify 
        PlayerData* data = loadPlayerData("TestPlayer"); 
        if (data) { 
            printf("   Updated stats:\n"); 
            printf("   - Total games: %d\n", data->totalGames); 
            printf("   - Total score: %d\n", data->totalScore); 
            free(data); 
        } 
    } else { 
        printf(" ❌ FAIL: Cannot update stats\n"); 
    } 
} 
 
void test_save_game() { 
    printf("\n=== Test 7: Save Game ===\n"); 
     
    SaveGame save; 
    strcpy(save.playerName, "TestPlayer"); 
    save.currentQuestion = 5; 
    save.playerPosition = 45; 
    save.playerCombo = 3; 
    save.aiPositions[0] = 50; 
    save.aiPositions[1] = 40; 
    save.aiPositions[2] = 42; 
    save.totalCorrect = 4; 
    save.totalWrong = 1; 
    save.difficulty = 2; 
     
    int result = saveGame(&save); 
     
    if (result) { 
        printf(" ✅ PASS: Game saved\n"); 
    } else { 
        printf(" ❌ FAIL: Cannot save game\n"); 
    } 
} 
 
void test_load_game() { 
    printf("\n=== Test 8: Load Game ===\n"); 
     
    SaveGame* save = loadGame("TestPlayer"); 
     
    if (save) { 
        printf(" ✅ PASS: Game loaded\n"); 
        printf("   Player: %s\n", save->playerName); 
        printf("   Question: %d\n", save->currentQuestion); 
        printf("   Position: %d%%\n", save->playerPosition); 
        printf("   Combo: %d\n", save->playerCombo); 
         
        free(save); 
    } else { 
        printf(" ⚠  WARNING: No saved game found\n"); 
    } 
} 
 
void test_backup_file() { 
    printf("\n=== Test 9: Backup File ===\n"); 
     
    int result = backupFile("data/save/leaderboard.txt"); 
     
    if (result) { 
        printf(" ✅ PASS: Backup created\n"); 
    } else { 
        printf(" ⚠  WARNING: No file to backup (OK if first run)\n"); 
    } 
} 
 
int main() { 
    printf("╔════════════════════════════════════════╗\n"); 
    printf("║    PERSON 5: Save/Load Tests           ║\n"); 
    printf("╚════════════════════════════════════════╝\n"); 
     
    test_create_directories(); 
    test_save_score(); 
    test_load_leaderboard(); 
    test_save_player_data(); 
    test_load_player_data(); 
    test_update_stats(); 
    test_save_game(); 
    test_load_game(); 
    test_backup_file(); 
     
    printf("\n╔════════════════════════════════════════╗\n"); 
    printf("║         All Tests Completed!           ║\n"); 
    printf("╚════════════════════════════════════════╝\n\n"); 
     
    return 0; 
}
