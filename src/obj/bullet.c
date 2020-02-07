#include "bullet.h"

Bullet bullets[BULLET_COUNT];

u8 BulletInit(u8 dir) {
    u8 i = BULLET_COUNT;

    while(i--) {
        if(!bullets[i].active) {
            bullets[i].dir = dir;
            bullets[i].x = BULLET_SOUTH_START_X;
            bullets[i].y = BULLET_SOUTH_START_Y;
            bullets[i].time = 0;
            DrawMap(bullets[i].x, bullets[i].y, mapBulletBigA);
            DrawMap(bullets[i].x, bullets[i].y + 1, mapBulletBigD);
            bullets[i].active = 1;
            return 1;
        }
    }

    return 0;
}

void BulletUpdate(u8 i) {
    u8 modRes;
    if(!bullets[i].active) {
        return;
    }

    bullets[i].time++;

    switch(bullets[i].dir) {
        default:
            if(bullets[i].time == 30) {
                bullets[i].active = 0;
                Fill(bullets[i].x, bullets[i].y, 1, 2, 0);
                return;
            } else if(bullets[i].time < 8) {
                if(!(bullets[i].time % 2)) {
                    Fill(bullets[i].x, bullets[i].y, 1, 2, 0);
                    bullets[i].x--;
                    DrawMap(bullets[i].x, bullets[i].y, mapBulletBigA);
                    DrawMap(bullets[i].x, bullets[i].y + 1, mapBulletBigD);
                } else {
                    DrawMap(bullets[i].x, bullets[i].y, mapBulletBigB);
                    DrawMap(bullets[i].x, bullets[i].y + 1, mapBulletBigC);
                }
            } else {
                modRes = bullets[i].time % 4;
                switch(modRes) {
                    case 1:
                        DrawMap(bullets[i].x, bullets[i].y, mapBulletSmallB);
                        DrawMap(bullets[i].x, bullets[i].y + 1, mapBulletSmallI);
                        break;
                    case 2:
                        DrawMap(bullets[i].x, bullets[i].y, mapBulletSmallC);
                        DrawMap(bullets[i].x, bullets[i].y + 1, mapBulletSmallH);
                        break;
                    case 3:
                        DrawMap(bullets[i].x, bullets[i].y, mapBulletSmallD);
                        DrawMap(bullets[i].x, bullets[i].y + 1, mapBulletSmallG);
                        break;
                    default:
                        Fill(bullets[i].x, bullets[i].y, 1, 2, 0);
                        bullets[i].x--;
                        DrawMap(bullets[i].x, bullets[i].y, mapBulletSmallA);
                        DrawMap(bullets[i].x, bullets[i].y + 1, mapBulletSmallJ);
                }
            }
    }
}