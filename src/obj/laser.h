#ifndef _LASER_H
#define _LASER_H

#include "../system/defines.h"
#include "../system/graphics.h"

#define LASER_COUNT 2

typedef struct {
    u8 active, x, y, w, h, time, tileIndex, backfeed;
    direction dir;
} Laser;

extern Laser lasers[];

void LaserUpdate(u8);
u8 LaserInit(direction, u8, u8);
void LaserDeactivate(u8);

#endif
