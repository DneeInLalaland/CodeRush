# 📋 PERSON 5: Save/Load System & Leaderboard

## Role & Responsibilities
Responsible for managing all persistent data in the game, including:
- Leaderboard (scores, ranks, difficulty, timestamp)
- Player statistics (games played, wins, best score, accuracy, combos)
- Game progress (save/load/delete)
- Auto-save system
- Backup management

---

## 🎯 Tasks Overview
1. ✅ Create directory management system  
2. ✅ Implement leaderboard save/load and sorting  
3. ✅ Implement player data save/load and stats update  
4. ✅ Implement game progress save/load and deletion  
5. ✅ Implement auto-save system  
6. ✅ Implement backup system  

---

## 📁 File Structure
save/ 
├── save.h # Header file with structs and function declarations 
└── save.c # Implementation of all save/load functions

data/ 
├── save/ # Player data, savegames, leaderboard 
└── backup/ # Backup files

---

## 🔧 Core Data Structures

### LeaderboardEntry
```c
typedef struct {
    char name[50];
    int score;
    int rank;
    time_t timestamp;
    int difficulty;
} LeaderboardEntry;

### PlayerData
typedef struct {
    char name[50];
    int totalGames;
    int wins;
    int totalScore;
    int bestScore;
    int totalCorrect;
    int totalWrong;
    int longestCombo;
    time_t lastPlayed;
} PlayerData;

### SaveGame
typedef struct {
    char playerName[50];
    int currentQuestion;
    int playerPosition;
    int playerCombo;
    int aiPositions[3];
    int totalCorrect;
    int totalWrong;
    int difficulty;
    time_t saveTime;
} SaveGame;

## 📚 Core Functions
### Directory & File Management
int createDirectories()
int fileExists(const char* path)
int backupFile(const char* path)
void cleanOldBackups(int daysOld)
void getCurrentDateTime(char* buffer, int size)

### Leaderboard
int saveScore(const char* name, int score, int rank, int difficulty)
LeaderboardEntry* loadLeaderboard(int* count)
void sortLeaderboard(LeaderboardEntry* entries, int count)
void displayTop10()

### Player Data
int savePlayerData(PlayerData* data)
PlayerData* loadPlayerData(const char* name)
int updatePlayerStats(const char* name, int score, int rank, int correct, int wrong, int combo)

### Game Progress
int saveGame(SaveGame* save)
SaveGame* loadGame(const char* playerName)
int deleteSave(const char* playerName)
int autoSaveProgress(...)
int hasSavedGame(const char* playerName)

## 🔌 Integration with Other Modules
Person 2 (Game Logic): calls saveGame, loadGame, updatePlayerStats, saveScore, deleteSave

Person 4 (UI Display): calls loadLeaderboard, loadPlayerData, displayTop10, displayPlayerStats

Person 3 (Input System): optional integration for saving input stats

Person 1 (Question System): optional integration for saving progress by question ID

## 📊 Usage Examples
### Example 1: Save Player Data
PlayerData p = {0};
strcpy(p.name, "TestPlayer");
p.totalGames = 5;
p.bestScore = 6000;
savePlayerData(&p);

### Example 2: Load Game
SaveGame* g = loadGame("TestPlayer");
if (g) {
    printf("Resuming from question %d\n", g->currentQuestion);
    free(g);
}

### ✅ Deliverables Checklist
[ ] save/save.h created
[ ] save/save.c implemented
[ ] Compiles without errors
[ ] Directories created automatically
[ ] Leaderboard works and sorts correctly
[ ] Player data save/load works
[ ] Game save/load works
[ ] Backup system functional
[ ] All functions documented
[ ] Integrated with other modules

## 🐛 Common Issues & Solutions
Directories not created → Call createDirectories() at program start
File write fails → Check permissions, use perror() for diagnostics
Leaderboard not sorted → Verify compareScores() logic
Binary read/write mismatch → Ensure struct sizes match

## 📚 Required Knowledge
File I/O: fopen, fread, fwrite, fclose
Directory ops: mkdir, stat
Memory: malloc, free
Sorting: qsort
Time: time(), localtime(), strftime()

## 🎓 Best Practices
1. Always call createDirectories() before saving
2. Backup before overwriting files
3. Validate all file operations
4. Free allocated memory after use
5. Test on both Windows and Linux

## 🎯 Summary
Person 5 is the "memory keeper" of the game:
✅ Saves and loads all persistent data
✅ Manages leaderboard and player stats
✅ Provides backup and auto-save
✅ Ensures data integrity across modules

Without this system, player progress and scores would be lost — making it a critical part of CodeRacer.
