#ifndef BULLET_H
#define BULLET_H

#include "../system/defines.h"
#include "../system/graphics.h"

#define BULLET_SPRITE_ID 8
#define BULLET_COUNT 2
#define BULLET_SPRITE_COUNT 4
#define BULLET_WIDTH 1
#define BULLET_HEIGHT 1

#define BULLET_SPRITE(b, i) (BULLET_SPRITE_ID + (b * BULLET_COUNT) + i)

#define BULLET_POINTS 16

typedef struct {
    u8 xTravel[BULLET_POINTS];
    u8 active, poweredUp, pointOfFire;
} Bullet;

extern Bullet bullets[];

void BulletInit(u8, u8 *, u8 *, u8);
u8 BulletUpdate(u8);

#endif