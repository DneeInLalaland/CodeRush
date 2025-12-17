// Karnsinee Nikrotamethanee (68070503412)
#include "save.h"
 
// Create required directories (data/, data/save/, data/backup/)
int createDirectories() {
    struct stat st = {0};
     
    // Create main data/ directory
    if (stat("data", &st) == -1) {
        mkdir("data", 0755);
        printf("Created directory: data/\n");
    }
     
    // Create data/save/ directory
    if (stat("data/save", &st) == -1) {
        mkdir("data/save", 0755);
        printf("Created directory: data/save/\n");
    }
     
    // Create data/backup/ directory
    if (stat("data/backup", &st) == -1) {
        mkdir("data/backup", 0755);
        printf("Created directory: data/backup/\n");
    }
     
    return 1;
}
 
// Check whether a file exists
int fileExists(const char* filepath) {
    FILE* file = fopen(filepath, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}
 
// Create a backup copy of a file
int backupFile(const char* filepath) {
    if (!fileExists(filepath)) {
        return 0;
    }
     
    // Generate backup file name
    char backupPath[256];
    char timestamp[32];
    getCurrentDateTime(timestamp, sizeof(timestamp));
     
    // Extract filename from path
    const char* filename = strrchr(filepath, '/');
    if (!filename) {
        filename = filepath;
    } else {
        filename++; // skip '/'
    }
     
    snprintf(backupPath, sizeof(backupPath),
             "data/backup/%s_%s.bak",
             filename, timestamp);
     
    // Copy file contents
    FILE* source = fopen(filepath, "rb");
    FILE* dest = fopen(backupPath, "wb");
     
    if (!source || !dest) {
        if (source) fclose(source);
        if (dest) fclose(dest);
        return 0;
    }
     
    char buffer[4096];
    size_t bytes;
     
    while ((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }
     
    fclose(source);
    fclose(dest);
     
    printf("Backup created: %s\n", backupPath);
    return 1;
}
 
// Remove old backup files (placeholder)
void cleanOldBackups(int daysOld) {
    // Basic example – can be extended later
    printf("Cleaning backups older than %d days...\n", daysOld);
    // TODO: Implement actual cleanup logic
}
 
// Get current date and time as a formatted string
void getCurrentDateTime(char* buffer, int size) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    strftime(buffer, size, "%Y%m%d_%H%M%S", t);
}
 
// Compare leaderboard scores (used for sorting)
int compareScores(const void* a, const void* b) {
    LeaderboardEntry* entryA = (LeaderboardEntry*)a;
    LeaderboardEntry* entryB = (LeaderboardEntry*)b;
     
    // Sort by score (descending)
    if (entryB->score != entryA->score) {
        return entryB->score - entryA->score;
    }
     
    // If scores are equal, sort by timestamp (older first)
    return difftime(entryA->timestamp, entryB->timestamp);
}
 
// Sort leaderboard entries
void sortLeaderboard(LeaderboardEntry* entries, int count) {
    qsort(entries, count, sizeof(LeaderboardEntry), compareScores);
}
 
// Save a new score to the leaderboard
int saveScore(const char* name, int score, int rank, int difficulty) {
    if (!name || strlen(name) == 0) {
        printf("❌ Error: Invalid name\n");
        return 0;
    }
     
    createDirectories();
     
    // Backup existing leaderboard file
    backupFile("data/save/leaderboard.txt");
     
    // Open file in append mode
    FILE* file = fopen("data/save/leaderboard.txt", "a");
    if (!file) {
        printf("❌ Error: Cannot open leaderboard file\n");
        return 0;
    }
     
    // Write data
    // Format: NAME|SCORE|RANK|DIFFICULTY|TIMESTAMP
    fprintf(file, "%s|%d|%d|%d|%ld\n",
            name, score, rank, difficulty, (long)time(NULL));
     
    fclose(file);
     
    printf("💾 Score saved to leaderboard!\n");
    return 1;
}
 
// Load leaderboard data from file
LeaderboardEntry* loadLeaderboard(int* count) {
    *count = 0;
     
    if (!fileExists("data/save/leaderboard.txt")) {
        printf("No leaderboard file found\n");
        return NULL;
    }
     
    // Count number of lines first
    FILE* file = fopen("data/save/leaderboard.txt", "r");
    if (!file) {
        return NULL;
    }
     
    char line[256];
    int lineCount = 0;
    while (fgets(line, sizeof(line), file)) {
        lineCount++;
    }
     
    rewind(file);
     
    // Allocate memory
    LeaderboardEntry* entries = (LeaderboardEntry*)malloc(
        sizeof(LeaderboardEntry) * lineCount);
     
    if (!entries) {
        fclose(file);
        return NULL;
    }
     
    // Read data
    int i = 0;
    while (fgets(line, sizeof(line), file) && i < lineCount) {
        long timestamp;
         
        // Parse format: NAME|SCORE|RANK|DIFFICULTY|TIMESTAMP
        if (sscanf(line, "%49[^|]|%d|%d|%d|%ld",
                   entries[i].name,
                   &entries[i].score,
                   &entries[i].rank,
                   &entries[i].difficulty,
                   &timestamp) == 5) {
             
            entries[i].timestamp = (time_t)timestamp;
            i++;
        }
    }
     
    *count = i;
    fclose(file);
     
    // Sort leaderboard
    sortLeaderboard(entries, *count);
     
    printf("Loaded %d leaderboard entries\n", *count);
    return entries;
}
 
// Display top 10 players
void displayTop10() {
    int count;
    LeaderboardEntry* entries = loadLeaderboard(&count);
     
    if (!entries || count == 0) {
        printf("No leaderboard data available.\n");
        return;
    }
     
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║                   🏆  TOP 10 PLAYERS  🏆                   ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
     
    int displayCount = (count < 10) ? count : 10;
     
    for (int i = 0; i < displayCount; i++) {
        char timeStr[32];
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d",
                 localtime(&entries[i].timestamp));
         
        const char* medal = "";
        if (i == 0) medal = " 🥇 ";
        else if (i == 1) medal = " 🥈 ";
        else if (i == 2) medal = " 🥉 ";
         
        printf("%2d. %s %-20s  Score: %5d  Rank: %d  (%s)\n",
               i + 1,
               medal,
               entries[i].name,
               entries[i].score,
               entries[i].rank,
               timeStr);
    }
     
    printf("\n");
     
    free(entries);
}

// Save player persistent data
int savePlayerData(PlayerData* data) {
    if (!data || strlen(data->name) == 0) {
        printf("❌ Error: Invalid player data\n");
        return 0;
    }

    createDirectories();

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "data/save/player_%s.dat", data->name);

    // Backup old player data
    backupFile(filepath);

    FILE* file = fopen(filepath, "wb");
    if (!file) {
        printf("❌ Error: Cannot save player data\n");
        return 0;
    }

    fwrite(data, sizeof(PlayerData), 1, file);
    fclose(file);

    printf("💾 Player data saved: %s\n", data->name);
    return 1;
}

// Load player persistent data
PlayerData* loadPlayerData(const char* name) {
    if (!name || strlen(name) == 0) return NULL;

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "data/save/player_%s.dat", name);

    if (!fileExists(filepath)) {
        printf("⚠️ No saved data for player: %s\n", name);
        return NULL;
    }

    FILE* file = fopen(filepath, "rb");
    if (!file) return NULL;

    PlayerData* data = (PlayerData*)malloc(sizeof(PlayerData));
    if (!data) {
        fclose(file);
        return NULL;
    }

    if (fread(data, sizeof(PlayerData), 1, file) != 1) {
        free(data);
        fclose(file);
        return NULL;
    }

    fclose(file);
    printf("📥 Player data loaded: %s\n", name);
    return data;
}

// Update cumulative player statistics
int updatePlayerStats(const char* name, int score, int rank, int correct, int wrong, int combo) {
    PlayerData* data = loadPlayerData(name);
    if (!data) {
        data = (PlayerData*)malloc(sizeof(PlayerData));
        if (!data) return 0;

        strncpy(data->name, name, sizeof(data->name) - 1);
        data->name[sizeof(data->name) - 1] = '\0';
        data->totalGames = 0;
        data->wins = 0;
        data->totalScore = 0;
        data->bestScore = 0;
        data->totalCorrect = 0;
        data->totalWrong = 0;
        data->longestCombo = 0;
        data->lastPlayed = 0;
    }

    data->totalGames++;
    if (rank == 1) data->wins++;
    data->totalScore += score;
    if (score > data->bestScore) data->bestScore = score;
    data->totalCorrect += correct;
    data->totalWrong += wrong;
    if (combo > data->longestCombo) data->longestCombo = combo;
    data->lastPlayed = time(NULL);

    int result = savePlayerData(data);
    free(data);
    return result;
}

// Save current game state
int saveGame(SaveGame* save) {
    if (!save || strlen(save->playerName) == 0) {
        printf("❌ Error: Invalid save data\n");
        return 0;
    }

    createDirectories();

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "data/save/savegame_%s.dat", save->playerName);

    // Backup old save file
    backupFile(filepath);

    FILE* file = fopen(filepath, "wb");
    if (!file) {
        printf("❌ Error: Cannot save game\n");
        return 0;
    }

    save->saveTime = time(NULL);
    fwrite(save, sizeof(SaveGame), 1, file);
    fclose(file);

    printf("💾 Game saved successfully!\n");
    return 1;
}

// Load saved game state
SaveGame* loadGame(const char* playerName) {
    if (!playerName || strlen(playerName) == 0) return NULL;

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "data/save/savegame_%s.dat", playerName);

    if (!fileExists(filepath)) {
        printf("⚠️ No saved game found for: %s\n", playerName);
        return NULL;
    }

    FILE* file = fopen(filepath, "rb");
    if (!file) return NULL;

    SaveGame* save = (SaveGame*)malloc(sizeof(SaveGame));
    if (!save) {
        fclose(file);
        return NULL;
    }

    if (fread(save, sizeof(SaveGame), 1, file) != 1) {
        free(save);
        fclose(file);
        return NULL;
    }

    fclose(file);

    printf("📥 Game loaded successfully!\n");
    printf(" Player: %s\n", save->playerName);
    printf(" Question: %d\n", save->currentQuestion);
    printf(" Position: %d%%\n", save->playerPosition);

    char timeStr[64];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(&save->saveTime));
    printf(" Saved: %s\n", timeStr);

    return save;
}
