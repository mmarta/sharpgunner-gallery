#ifndef _LEVEL_H
#define _LEVEL_H

#include "defines.h"
#include "../obj/player.h"
#include "../obj/enemy.h"

typedef struct {
    u8 invaderFactor, sweeperFactor, sparxFactor, nucleusFactor, asteroidFactor,
        randomFactor, minGenTime;
    u16 bonus;
} Level;

extern const Level levels[];
extern u8 levelTime, levelTick;

void LevelUpdate();

#endif
