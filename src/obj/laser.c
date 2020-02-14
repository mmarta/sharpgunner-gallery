#include "laser.h"

Laser lasers[LASER_COUNT];

u8 LaserInit(u8 dir, u8 x, u8 y) {
    u8 i = LASER_COUNT;

    while(i--) {
        if(!lasers[i].active) {
            lasers[i].dir = dir;
            lasers[i].x = x;
            lasers[i].y = y;
            lasers[i].time = 0;
            lasers[i].tileIndex = 0;
            switch(dir) {
                case DIR_WEST:
                case DIR_EAST:
                    DrawMap(lasers[i].x, lasers[i].y, mapLaserHorizontal[lasers[i].tileIndex]);
                    break;
                default:
                    DrawMap(lasers[i].x, lasers[i].y, mapLaserVertical[lasers[i].tileIndex]);
            }
            
            lasers[i].active = 1;
            return 1;
        }
    }

    return 0;
}

void LaserUpdate(u8 i) {
    if(!lasers[i].active) {
        return;
    }

    lasers[i].time += 2;

    if(lasers[i].time == 20) {
        lasers[i].active = 0;
        if(lasers[i].dir == DIR_EAST || lasers[i].dir == DIR_WEST) {
            Fill(lasers[i].x, lasers[i].y, 2, 1, 0);
        } else {
            Fill(lasers[i].x, lasers[i].y, 1, 2, 0);
        }
        return;
    } else if(lasers[i].time < 4) {
        if(lasers[i].time % 2 == 0) {
            lasers[i].tileIndex++;
        }
    } else if(lasers[i].time < 16) {
        if(lasers[i].time % 4 == 0) {
            lasers[i].tileIndex++;
        }
    } else {
        if(lasers[i].time % 2 == 0) {
            lasers[i].tileIndex++;
        }
    }

    if(lasers[i].time % 2) {
        return;
    }

    switch(lasers[i].dir) {
        case DIR_WEST:
            Fill(lasers[i].x, lasers[i].y, 2, 1, 0);
            lasers[i].y--;
            DrawMap(lasers[i].x, lasers[i].y, mapLaserHorizontal[lasers[i].tileIndex]);
            break;
        case DIR_EAST:
            Fill(lasers[i].x, lasers[i].y, 2, 1, 0);
            lasers[i].y++;
            DrawMap(lasers[i].x, lasers[i].y, mapLaserHorizontal[lasers[i].tileIndex]);
            break;
        case DIR_NORTH:
            Fill(lasers[i].x, lasers[i].y, 1, 2, 0);
            lasers[i].x++;
            DrawMap(lasers[i].x, lasers[i].y, mapLaserVertical[lasers[i].tileIndex]);
            break;
        default:
            Fill(lasers[i].x, lasers[i].y, 1, 2, 0);
            lasers[i].x--;
            DrawMap(lasers[i].x, lasers[i].y, mapLaserVertical[lasers[i].tileIndex]);
    }
}