#ifndef LASER_H
#define LASER_H

#include "../system/defines.h"
#include "../system/graphics.h"

#define LASER_SOUTH_START_X 27
#define LASER_SOUTH_START_Y 13

typedef struct {
    u8 active, dir, x, y, time;
} Laser;

extern Laser laser;

void LaserUpdate();
void LaserInit(u8);

#endif