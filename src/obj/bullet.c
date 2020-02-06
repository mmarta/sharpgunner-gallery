#include "bullet.h"

Bullet bullets[BULLET_COUNT];

void BulletInit(u8 poweredUp, u8 *sX, u8 *sY, u8 tX) {
    u8 i = 0, half, quarter, eighth;
    tX += 8;
    while(i < BULLET_COUNT) {
        if(!bullets[i].active && !bullets[i + 1].active) {
            bullets[i].active = 1;
            bullets[i].pointOfFire = 0xff;
            bullets[i].poweredUp = poweredUp;
            bullets[i + 1].active = 1;
            bullets[i + 1].poweredUp = poweredUp;
            bullets[i + 1].pointOfFire = 0xff;
            MapSprite(BULLET_SPRITE_ID + i, spriteMapBulletA);
            MoveSprite(BULLET_SPRITE_ID + i, *sX, *sY, BULLET_W, BULLET_H);
            MapSprite(BULLET_SPRITE_ID + i + 1, spriteMapBulletA);
            MoveSprite(BULLET_SPRITE_ID + i + 1, *sX, *sY + 8, BULLET_W, BULLET_H);

            // Target
            bullets[i].xTravel[7] = tX;
            bullets[i + 1].xTravel[7] = tX;

            // Half
            half = (*sX - tX) >> 1;
            bullets[i].xTravel[3] = *sX - half;
            bullets[i + 1].xTravel[3] = *sX - half;

            // Quarter
            quarter = (*sX - tX) >> 2;
            bullets[i].xTravel[1] = *sX - quarter;
            bullets[i].xTravel[5] = bullets[i].xTravel[3] - quarter;
            bullets[i + 1].xTravel[1] = *sX - quarter;
            bullets[i + 1].xTravel[5] = bullets[i + 1].xTravel[3] - quarter;

            // Eighth
            eighth = (*sX - tX) >> 3;
            bullets[i].xTravel[0] = *sX - eighth;
            bullets[i].xTravel[2] = bullets[i].xTravel[1] - eighth;
            bullets[i].xTravel[4] = bullets[i].xTravel[3] - eighth;
            bullets[i].xTravel[6] = bullets[i].xTravel[5] - eighth;
            bullets[i + 1].xTravel[0] = *sX - eighth;
            bullets[i + 1].xTravel[2] = bullets[i + 1].xTravel[1] - eighth;
            bullets[i + 1].xTravel[4] = bullets[i + 1].xTravel[3] - eighth;
            bullets[i + 1].xTravel[6] = bullets[i + 1].xTravel[5] - eighth;

            return;
        }
        // BULLET_SPRITE_ID
        i += 2;
    }
}

void BulletUpdate(u8 i) {
    if(!bullets[i].active) {
        return;
    }

    bullets[i].pointOfFire++;
    if(bullets[i].pointOfFire >= BULLET_POINTS) {
        bullets[i].active = 0;
        HideSprite(BULLET_SPRITE_ID + i, BULLET_W, BULLET_H);
        return;
    }

    switch(bullets[i].pointOfFire) {
        case 0:
            MapSprite(BULLET_SPRITE_ID + i, spriteMapBulletA);
            break;
        case 2:
            MapSprite(BULLET_SPRITE_ID + i, spriteMapBulletB);
            break;
        case 4:
            MapSprite(BULLET_SPRITE_ID + i, spriteMapBulletC);
            break;
        case 6:
            MapSprite(BULLET_SPRITE_ID + i, spriteMapBulletD);
            break;
    }
    MoveSprite(BULLET_SPRITE_ID + i, bullets[i].xTravel[bullets[i].pointOfFire], sprites[BULLET_SPRITE_ID + i].y, BULLET_W, BULLET_H);
}