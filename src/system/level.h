#ifndef _LEVEL_H
#define _LEVEL_H

#include "defines.h"

typedef struct {
    u8 invaderFactor, sweeperFactor, sparxFactor, nucleusFactor, asteroidFactor,
        randomFactor, enemyTotal, minGenTime;
    u16 bonus;
} Level;

extern const Level levels[];

#endif
