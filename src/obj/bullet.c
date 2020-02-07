#include "bullet.h"

Bullet bullets[BULLET_COUNT];

void BulletInit(u8 poweredUp, u8 *sX, u8 *sY, u8 tX) {
    u8 i = 0, half, quarter, eighth, sixteenth;
    tX += 8;
    while(i < BULLET_COUNT) {
        if(!bullets[i].active) {
            bullets[i].active = 1;
            bullets[i].pointOfFire = 0xff;
            bullets[i].poweredUp = poweredUp;
            MapSprite(BULLET_SPRITE(i, 0), spriteMapBulletA);
            MoveSprite(BULLET_SPRITE(i, 0), *sX, *sY, BULLET_WIDTH, BULLET_HEIGHT);
            MapSprite(BULLET_SPRITE(i, 1), spriteMapBulletA);
            MoveSprite(BULLET_SPRITE(i, 1), *sX, *sY + 8, BULLET_WIDTH, BULLET_HEIGHT);

            // Target
            bullets[i].xTravel[15] = tX;
            bullets[i + 1].xTravel[15] = tX;

            // Half
            half = (*sX - tX) >> 1;
            bullets[i].xTravel[7] = *sX - half;

            // Quarter
            quarter = (*sX - tX) >> 2;
            bullets[i].xTravel[3] = *sX - quarter;
            bullets[i].xTravel[11] = bullets[i].xTravel[7] - quarter;

            // Eighth
            eighth = (*sX - tX) >> 3;
            bullets[i].xTravel[1] = *sX - eighth;
            bullets[i].xTravel[5] = bullets[i].xTravel[3] - eighth;
            bullets[i].xTravel[9] = bullets[i].xTravel[7] - eighth;
            bullets[i].xTravel[13] = bullets[i].xTravel[11] - eighth;

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
            }

            return;
        }
        // BULLET_SPRITE_ID
        i++;
    }
}

u8 BulletUpdate(u8 i) {
    u8 retVal = 0;
    if(!bullets[i].active) {
        return 0;
    }

    bullets[i].pointOfFire += (bullets[i].poweredUp ? 2 : 1);
    if(bullets[i].pointOfFire >= BULLET_POINTS) {
        if(sprites[BULLET_SPRITE(i, 0)].x < 40 && sprites[BULLET_SPRITE(i, 0)].y > 208) {
            retVal = 1;
        }
        bullets[i].active = 0;
        HideSprite(BULLET_SPRITE(i, 0), BULLET_WIDTH, BULLET_HEIGHT);
        HideSprite(BULLET_SPRITE(i, 1), BULLET_WIDTH, BULLET_HEIGHT);
        return retVal;
    }

    switch(bullets[i].pointOfFire) {
        case 3:
            MapSprite(BULLET_SPRITE(i, 0), spriteMapBulletB);
            MapSprite(BULLET_SPRITE(i, 1), spriteMapBulletB);
            MoveSprite(BULLET_SPRITE(i, 0), sprites[BULLET_SPRITE(i, 0)].x, sprites[BULLET_SPRITE(i, 0)].y + 1, BULLET_WIDTH, BULLET_HEIGHT);
            MoveSprite(BULLET_SPRITE(i, 1), sprites[BULLET_SPRITE(i, 1)].x, sprites[BULLET_SPRITE(i, 1)].y - 1, BULLET_WIDTH, BULLET_HEIGHT);
            break;
        case 5:
            MapSprite(BULLET_SPRITE(i, 0), spriteMapBulletC);
            MapSprite(BULLET_SPRITE(i, 1), spriteMapBulletC);
            MoveSprite(BULLET_SPRITE(i, 0), sprites[BULLET_SPRITE(i, 0)].x, sprites[BULLET_SPRITE(i, 0)].y + 1, BULLET_WIDTH, BULLET_HEIGHT);
            MoveSprite(BULLET_SPRITE(i, 1), sprites[BULLET_SPRITE(i, 1)].x, sprites[BULLET_SPRITE(i, 1)].y - 1, BULLET_WIDTH, BULLET_HEIGHT);
            break;
        case 9:
            MapSprite(BULLET_SPRITE(i, 0), spriteMapBulletD);
            MapSprite(BULLET_SPRITE(i, 1), spriteMapBulletD);
            MoveSprite(BULLET_SPRITE(i, 0), sprites[BULLET_SPRITE(i, 0)].x, sprites[BULLET_SPRITE(i, 0)].y + 1, BULLET_WIDTH, BULLET_HEIGHT);
            MoveSprite(BULLET_SPRITE(i, 1), sprites[BULLET_SPRITE(i, 1)].x, sprites[BULLET_SPRITE(i, 1)].y - 1, BULLET_WIDTH, BULLET_HEIGHT);
            break;
    }
    MoveSprite(BULLET_SPRITE(i, 0), bullets[i].xTravel[bullets[i].pointOfFire], sprites[BULLET_SPRITE(i, 0)].y, BULLET_WIDTH, BULLET_HEIGHT);
    MoveSprite(BULLET_SPRITE(i, 1), bullets[i].xTravel[bullets[i].pointOfFire], sprites[BULLET_SPRITE(i, 1)].y, BULLET_WIDTH, BULLET_HEIGHT);

    return 0;
}