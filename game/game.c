// Varakron Vimolgarnjana (68070503452)
#include "game.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

// --------- internal helpers ---------
#ifdef _WIN32
#include <windows.h>
double now_sec(void) {
    return (double)GetTickCount() / 1000.0;
}
#else
double now_sec(void) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}
#endif

static float comboBonusDistance(int combo){
    if (combo >= 7) return 10.0f;
    if (combo >= 5) return 5.0f;
    if (combo >= 3) return 2.0f;
    return 0.0f;
}

static float speedFromComboPlayer(int combo){
    if (combo >= 7) return 12.0f;
    if (combo >= 5) return 9.0f;
    if (combo >= 3) return 7.0f;
    return 5.0f;
}

static float rollAICorrectProb(Difficulty d){
    int p = 75;
    switch(d){
        case D1: p = 75; break;
        case D2: p = 70; break;
        case D3: p = 65; break;
        case D4: p = 60; break;
        case D5: p = 55; break;
        default: p = 65; break;
    }
    int r = rand()%100; // 0..99
    return (r < p) ? 1.0f : 0.0f;
}

static void markFinishIfNeeded(GameState* gs, Racer* r){
    if (!r->finished && r->position >= gs->finishLine){
        r->finished = true;
        r->finishRank = ++gs->carsFinished;
        if (!r->isAI && gs->finalRankPlayer == 0){
            gs->finalRankPlayer = r->finishRank;
        }
    }
}

// --------- API impl ---------
void initGame(GameState* gs, const char* playerName, GameMode mode, Difficulty diff, int totalQuestions){
    memset(gs, 0, sizeof(*gs));
    srand((unsigned)time(NULL));
    gs->mode = mode;
    gs->difficulty = diff;
    if (totalQuestions < 1) totalQuestions = 1;
    if (totalQuestions > MAX_QUESTIONS_PER_RACE) totalQuestions = MAX_QUESTIONS_PER_RACE;
    gs->totalQuestions = totalQuestions;
    gs->finishLine = TRACK_LENGTH;
    gs->baseMove = gs->finishLine / (float)gs->totalQuestions;
    gs->finalRankPlayer = 0;
    gs->startTimeSec = now_sec();

    // player
    memset(&gs->player, 0, sizeof(Racer));
    snprintf(gs->player.name, sizeof(gs->player.name), "%s", (playerName?playerName:"Player"));
    gs->player.speed = 5.0f;
    gs->player.isAI = false;

    // AIs
    for (int i=0;i<NUM_AI_CARS;++i){
        memset(&gs->ai[i], 0, sizeof(Racer));
        snprintf(gs->ai[i].name, sizeof(gs->ai[i].name), "AI-%d", i+1);
        gs->ai[i].speed = 5.0f;
        gs->ai[i].isAI = true;
    }
}

void updateRaceOnPlayerAnswer(GameState* gs, bool correct){
    if (gs->finished) return;
    if (gs->currentQuestionIdx >= gs->totalQuestions) return;

    Racer* p = &gs->player;

    if (correct){
        p->totalCorrect += 1;
        p->combo += 1;
        float dist = gs->baseMove + comboBonusDistance(p->combo);
        p->position += dist;
        // speed boost only for player
        p->speed = speedFromComboPlayer(p->combo);
    }else{
        p->totalWrong += 1;
        p->combo = 0;
        p->speed = WRONG_PENALTY_SPEED;
        // (optional) small slowdown penalty on position
        // p->position += 0.0f;
    }

    // advance question index
    gs->currentQuestionIdx += 1;
}

void updateAICars(GameState* gs){
    if (gs->finished) return;

    for (int i=0;i<NUM_AI_CARS;++i){
        Racer* a = &gs->ai[i];
        if (a->finished) continue;

        bool correct = rollAICorrectProb(gs->difficulty) > 0.0f;
        if (correct){
            a->totalCorrect += 1;
            a->combo += 1;
            float dist = gs->baseMove + comboBonusDistance(a->combo);
            a->position += dist;
            // AI doesn't get speed boost, keep constant visual speed-ish
            a->speed = 6.0f; // mild visual change
        }else{
            a->totalWrong += 1;
            a->combo = 0;
            a->speed = WRONG_PENALTY_SPEED;
        }
    }
}

void checkFinish(GameState* gs){
    // players / AIs
    markFinishIfNeeded(gs, &gs->player);
    for (int i=0;i<NUM_AI_CARS;++i){
        markFinishIfNeeded(gs, &gs->ai[i]);
    }

    // End conditions:
    // 1) someone reaches finish line (let all keep going until player also finishes?)
    // For sprint: stop when any car finishes.
    bool anyFinished = gs->player.finished;
    for (int i=0;i<NUM_AI_CARS;++i){
        anyFinished = anyFinished || gs->ai[i].finished;
    }

    // 2) or questions exhausted
    bool outOfQuestions = (gs->currentQuestionIdx >= gs->totalQuestions);

    if (anyFinished || outOfQuestions){
        // assign ranks by current position for those not finished
        // collect racers into temp array to sort
        Racer all[1+NUM_AI_CARS];
        all[0] = gs->player;
        for (int i=0;i<NUM_AI_CARS;++i) all[1+i] = gs->ai[i];

        // assign temporary ranks for unfinished by position order
        // simple selection for 4 racers
        int rankCounter = gs->carsFinished + 1;
        // create indices
        int idx[1+NUM_AI_CARS] = {0,1,2,3};
        // mark finished have rank already
        for (int r=0;r<4;++r){
            if (all[idx[r]].finished) continue;
            // find the largest position among unfinished
            int best = r;
            for (int k=r+1;k<4;++k){
                if (all[idx[k]].finished) continue;
                if (all[idx[k]].position > all[idx[best]].position){
                    best = k;
                }
            }
            // swap
            if (best != r){
                int t = idx[r]; idx[r] = idx[best]; idx[best] = t;
            }
            // assign rank
            int id = idx[r];
            if (!all[id].finished){
                all[id].finished = true;
                all[id].finishRank = rankCounter++;
            }
        }

        // write back ranks
        // player
        if (!gs->player.finished){
            // find player's record in all[0]
            gs->player.finished = all[0].finished;
            gs->player.finishRank = all[0].finishRank;
            if (gs->finalRankPlayer == 0) gs->finalRankPlayer = gs->player.finishRank;
        }
        // AIs
        for (int i=0;i<NUM_AI_CARS;++i){
            if (!gs->ai[i].finished){
                gs->ai[i].finished = all[1+i].finished;
                gs->ai[i].finishRank = all[1+i].finishRank;
            }
        }

        gs->finished = true;
        gs->endTimeSec = now_sec();
    }
}

int calculateScore(const GameState* gs){
    int score = 0;
    const Racer* p = &gs->player;
    // base
    score += p->totalCorrect * 200; // Increased from 100 to 200
    score -= p->totalWrong * 50;
    if (score < 0) score = 0;

    // distance bonus
    score += (int)roundf(p->position);

    // rank bonus
    if (gs->finalRankPlayer == 1) score += 1500; // Increased from 1000 to 1500
    else if (gs->finalRankPlayer == 2) score += 1000; // Increased from 500 to 1000
    else if (gs->finalRankPlayer == 3) score += 500; // Increased from 250 to 500
    else score += 200; // Increased from 100 to 200

    // time bonus (faster is better)
    if (gs->endTimeSec > gs->startTimeSec){
        double dur = gs->endTimeSec - gs->startTimeSec;
        // simple inverse scaling
        int timeBonus = (int)fmax(0.0, 500.0 - dur * 10.0);
        score += timeBonus;
    }
    if (score < 0) score = 0;
    return score;
}

bool isRaceOver(const GameState* gs){
    return gs->finished;
}

void freeGame(GameState* gs){
    (void)gs;
    // placeholder: nothing to free yet
}

int calculateAdaptiveDifficulty(Difficulty baseDiff, int currentCombo) {
    // Rule: Increase difficulty by 1 for every 3 combo points
    int bonus = currentCombo / 3;
    
    int target = (int)baseDiff + bonus;
    
    // Cap at 5 (Master)
    if (target > 5) target = 5;
    
    return target;
}
