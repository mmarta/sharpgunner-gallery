#ifndef BULLET_H
#define BULLET_H

#include "../system/defines.h"
#include "../system/graphics.h"

#define BULLET_COUNT 2

#define BULLET_SOUTH_START_X 27
#define BULLET_SOUTH_START_Y 13

typedef struct {
    u8 active, dir, x, y, time;
} Bullet;

extern Bullet bullets[];

void BulletUpdate(u8);
u8 BulletInit(u8);

#endif