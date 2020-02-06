#include "bullet.h"

Bullet bullets[BULLET_COUNT];

void BulletInit(u8 poweredUp, u8 *sX, u8 *sY, u8 tX) {
    u8 i = 0, half, quarter, eighth, sixteenth;
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
            MoveSprite(BULLET_SPRITE_ID + i, *sX, *sY, BULLET_WIDTH, BULLET_HEIGHT);
            MapSprite(BULLET_SPRITE_ID + i + 1, spriteMapBulletA);
            MoveSprite(BULLET_SPRITE_ID + i + 1, *sX, *sY + 8, BULLET_WIDTH, BULLET_HEIGHT);

            // Target
            bullets[i].xTravel[15] = tX;
            bullets[i + 1].xTravel[15] = tX;

            // Half
            half = (*sX - tX) >> 1;
            bullets[i].xTravel[7] = *sX - half;
            bullets[i + 1].xTravel[7] = *sX - half;

            // Quarter
            quarter = (*sX - tX) >> 2;
            bullets[i].xTravel[3] = *sX - quarter;
            bullets[i].xTravel[11] = bullets[i].xTravel[7] - quarter;
            bullets[i + 1].xTravel[3] = *sX - quarter;
            bullets[i + 1].xTravel[11] = bullets[i + 1].xTravel[7] - quarter;

            // Eighth
            eighth = (*sX - tX) >> 3;
            bullets[i].xTravel[1] = *sX - eighth;
            bullets[i].xTravel[5] = bullets[i].xTravel[3] - eighth;
            bullets[i].xTravel[9] = bullets[i].xTravel[7] - eighth;
            bullets[i].xTravel[13] = bullets[i].xTravel[11] - eighth;
            bullets[i + 1].xTravel[1] = *sX - eighth;
            bullets[i + 1].xTravel[5] = bullets[i + 1].xTravel[3] - eighth;
            bullets[i + 1].xTravel[9] = bullets[i + 1].xTravel[7] - eighth;
            bullets[i + 1].xTravel[13] = bullets[i + 1].xTravel[11] - eighth;

            if(!poweredUp) {
                // Sixteenth
                sixteenth = (*sX - tX) >> 4;
                bullets[i].xTravel[0] = *sX - sixteenth;
                bullets[i].xTravel[2] = bullets[i].xTravel[1] - sixteenth;
                bullets[i].xTravel[4] = bullets[i].xTravel[3] - sixteenth;
                bullets[i].xTravel[6] = bullets[i].xTravel[5] - sixteenth;
                bullets[i].xTravel[8] = bullets[i].xTravel[7] - sixteenth;
                bullets[i].xTravel[10] = bullets[i].xTravel[9] - sixteenth;
                bullets[i].xTravel[12] = bullets[i].xTravel[11] - sixteenth;
                bullets[i].xTravel[14] = bullets[i].xTravel[13] - sixteenth;
                bullets[i + 1].xTravel[0] = *sX - sixteenth;
                bullets[i + 1].xTravel[2] = bullets[i].xTravel[1] - sixteenth;
                bullets[i + 1].xTravel[4] = bullets[i].xTravel[3] - sixteenth;
                bullets[i + 1].xTravel[6] = bullets[i].xTravel[5] - sixteenth;
                bullets[i + 1].xTravel[8] = bullets[i].xTravel[7] - sixteenth;
                bullets[i + 1].xTravel[10] = bullets[i].xTravel[9] - sixteenth;
                bullets[i + 1].xTravel[12] = bullets[i].xTravel[11] - sixteenth;
                bullets[i + 1].xTravel[14] = bullets[i].xTravel[13] - sixteenth;
            }

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

    bullets[i].pointOfFire += (bullets[i].poweredUp ? 2 : 1);
    if(bullets[i].pointOfFire >= BULLET_POINTS) {
        bullets[i].active = 0;
        HideSprite(BULLET_SPRITE_ID + i, BULLET_WIDTH, BULLET_HEIGHT);
        return;
    }

    switch(bullets[i].pointOfFire) {
        case 3:
            MapSprite(BULLET_SPRITE_ID + i, spriteMapBulletA);
            break;
        case 7:
            MapSprite(BULLET_SPRITE_ID + i, spriteMapBulletB);
            MoveSprite(BULLET_SPRITE_ID + i, sprites[BULLET_SPRITE_ID + i].x, sprites[BULLET_SPRITE_ID + i].y + (i % 2 ? -1 : 1), BULLET_WIDTH, BULLET_HEIGHT);
            break;
        case 11:
            MapSprite(BULLET_SPRITE_ID + i, spriteMapBulletC);
            MoveSprite(BULLET_SPRITE_ID + i, sprites[BULLET_SPRITE_ID + i].x, sprites[BULLET_SPRITE_ID + i].y + (i % 2 ? -1 : 1), BULLET_WIDTH, BULLET_HEIGHT);
            break;
        case 15:
            MapSprite(BULLET_SPRITE_ID + i, spriteMapBulletD);
            MoveSprite(BULLET_SPRITE_ID + i, sprites[BULLET_SPRITE_ID + i].x, sprites[BULLET_SPRITE_ID + i].y + (i % 2 ? -1 : 1), BULLET_WIDTH, BULLET_HEIGHT);
            break;
    }
    MoveSprite(BULLET_SPRITE_ID + i, bullets[i].xTravel[bullets[i].pointOfFire], sprites[BULLET_SPRITE_ID + i].y, BULLET_WIDTH, BULLET_HEIGHT);
}