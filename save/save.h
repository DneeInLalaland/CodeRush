// Karnsinee Nikrotamethanee (68070503412)
#ifndef SAVE_H
#define SAVE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
 
#ifdef _WIN32
    #include <direct.h>
    #define mkdir(path, mode) _mkdir(path)
#else
    #include <sys/types.h>
#endif
 
// Leaderboard entry structure
typedef struct {
    char name[50];       // Player name
    int score;           // Score value
    int rank;            // Final rank (1–4)
    time_t timestamp;    // Time when the game was played
    int difficulty;      // Difficulty level
} LeaderboardEntry;
 
// Player persistent data structure
typedef struct {
    char name[50];       // Player name
    int totalGames;      // Total games played
    int wins;            // Number of wins (rank 1)
    int totalScore;      // Accumulated score
    int bestScore;       // Highest score achieved
    int totalCorrect;    // Total correct answers
    int totalWrong;      // Total wrong answers
    int longestCombo;    // Longest combo achieved
    time_t lastPlayed;   // Last played timestamp
} PlayerData;
 
// Save game state structure
typedef struct {
    char playerName[50]; // Player name
    int currentQuestion; // Current question index
    int playerPosition;  // Player car position
    int playerCombo;     // Current combo count
    int aiPositions[3];  // AI car positions
    int totalCorrect;    // Total correct answers
    int totalWrong;      // Total wrong answers
    int difficulty;      // Difficulty level
    time_t saveTime;     // Save timestamp
} SaveGame;
 
// Leaderboard functions
int saveScore(const char* name, int score, int rank, int difficulty);
LeaderboardEntry* loadLeaderboard(int* count);
void sortLeaderboard(LeaderboardEntry* entries, int count);
void displayTop10();
 
// Player data functions
int savePlayerData(PlayerData* data);
PlayerData* loadPlayerData(const char* name);
int updatePlayerStats(const char* name, int score, int rank, int correct, int wrong, int combo);
 
// Save / Load game functions
int saveGame(SaveGame* save);
SaveGame* loadGame(const char* playerName);
int deleteSave(const char* playerName);
 
// File management utilities
int createDirectories();
int fileExists(const char* filepath);
int backupFile(const char* filepath);
void cleanOldBackups(int daysOld);
 
// Helper functions
void getCurrentDateTime(char* buffer, int size);
int compareScores(const void* a, const void* b);

#endif // SAVE_H
