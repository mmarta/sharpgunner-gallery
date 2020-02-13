#ifndef LASER_H
#define LASER_H

#include "../system/defines.h"
#include "../system/graphics.h"

#define LASER_COUNT 2

typedef struct {
    u8 active, dir, x, y, time, tileIndex, backfeed;
} Laser;

extern Laser lasers[];

void LaserUpdate(u8);
u8 LaserInit(u8, u8, u8);

#endif