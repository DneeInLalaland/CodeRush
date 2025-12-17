//Varakron Vimolgarnjana (68070503452)
#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// =========================
// Constants & Tunables
// =========================
#define NUM_AI_CARS 3
#define TRACK_LENGTH 1000.0f       // finish line position
// BASE_MOVE removed, calculated dynamically
#define WRONG_PENALTY_SPEED 5.0f   // speed reset on wrong
#define MAX_QUESTIONS_PER_RACE 40  // safety cap

// =========================
// Game Modes / Difficulty
// =========================
typedef enum {
    MODE_SPRINT = 0,
    MODE_VS     = 1,
    MODE_SURVIVAL = 2,
    MODE_TUTORIAL = 3
} GameMode;

typedef enum {
    D1 = 1, D2, D3, D4, D5
} Difficulty;

// =========================
// Racer & GameState
// =========================
typedef struct {
    char name[32];
    float position;      // current progress along the track
    float speed;         // current car speed (visual)
    int combo;           // consecutive correct answers
    int totalCorrect;
    int totalWrong;
    bool isAI;
    bool finished;       // reached finish
    int  finishRank;     // 1..4 if finished
} Racer;

typedef struct {
    GameMode mode;
    Difficulty difficulty;
    int totalQuestions;     // total questions in this race session
    int currentQuestionIdx; // 0-based
    float finishLine;       // usually TRACK_LENGTH
    float baseMove;         // calculated: TRACK_LENGTH / totalQuestions
    bool finished;          // whole race finished (any end condition)
    int  finalRankPlayer;   // 1..4 when finished
    
    // timing
    double startTimeSec;
    double endTimeSec;

    // actors
    Racer player;
    Racer ai[NUM_AI_CARS];

    // internal
    int carsFinished;       // how many cars have finished
} GameState;

// =========================
// Public API
// =========================

// Initialize the game state (Player name, mode, difficulty, number of questions).
// totalQuestions will be clamped to [1, MAX_QUESTIONS_PER_RACE].
void initGame(GameState* gs, const char* playerName, GameMode mode, Difficulty diff, int totalQuestions);

// Apply the player's answer result (true=correct, false=wrong).
// Advances question index and applies movement, speed/combos, etc.
void updateRaceOnPlayerAnswer(GameState* gs, bool correct);

// Advance AI cars based on difficulty probabilities and combo rules.
// Should be called once per "question tick" (i.e., after player answered one).
void updateAICars(GameState* gs);

// Check and update finish state for all cars; set ranks in finish order.
// Also sets gs->finished and gs->finalRankPlayer when the race has ended.
void checkFinish(GameState* gs);

// Compute final score (simple baseline formula).
// Returns a non-negative integer.
int calculateScore(const GameState* gs);

// Utility: is the race over?
bool isRaceOver(const GameState* gs);

// Cleanup if needed (placeholder for future extensions).
void freeGame(GameState* gs);

// NEW! Adaptive Difficulty
int calculateAdaptiveDifficulty(Difficulty baseDiff, int currentCombo);

#ifdef __cplusplus
}
#endif

#endif // GAME_H
