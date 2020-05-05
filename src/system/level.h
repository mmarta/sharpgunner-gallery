#ifndef _LEVEL_H
#define _LEVEL_H

#include "defines.h"
#include "../audio/audio.h"
#include "machine.h"
#include "../obj/player.h"
#include "../obj/enemy.h"

typedef struct {
    u8 invaderFactor, sweeperFactor, sparxFactor, nucleusFactor, asteroidFactor,
        randomFactor, minGenTime;
    u16 bonus;
} Level;

extern const Level levels[];
extern u8 levelTime, levelTick;

void LevelStart();
void LevelDisplayReady(u8);
void LevelUpdate();
u8 LevelPlayerDeath();

#define CLEAR_LEVEL() Fill(2, 0, 28, 28, 0)

#endif
