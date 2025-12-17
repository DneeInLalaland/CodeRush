//Warattaya Lekma
//68070503480

// graphics.h - Graphics and Display Functions
#ifndef GRAPHICS_H //continue reading the code below
#define GRAPHICS_H //defind GRAPHICS_H

#include <stdio.h>
#include "ui.h"  //helper functions from ui.h


#include "../game/game.h" //import game.h from previous folder

// ========================================
// CAR SPRITE FUNCTIONS
/*
 - draw car
 - @param isPlayer => 1 = player (🏎), 0 = AI (🤖)
 */
void drawCarSprite(int isPlayer); //declare draw car function

// ========================================
// RACE TRACK DISPLAY
/*
 - draw race track
 - @param game - GameState from Nuree
 - CONFIRMED from Nuree- GameState :
   - game->currentQuestion (int)
   - game->totalQuestions (int)
   - game->player.position (int)
   - game->player.combo (int)
   - game->player.totalCorrect (int)
   - game->player.totalWrong (int)
   - game->aiCars[i].name (char[50])
   - game->aiCars[i].position (int)
   - game->startTime (time_t)
 */
void drawRaceTrack(GameState* game); //declare draw race track function

#endif
