#include "laser.h"

Laser lasers[LASER_COUNT];

u8 LaserInit(direction dir, u8 x, u8 y) {
    u8 i = LASER_COUNT;

    while(i--) {
        if(!lasers[i].active) {
            lasers[i].dir = dir;
            lasers[i].x = x;
            lasers[i].y = y;
            lasers[i].time = 0;
            lasers[i].tileIndex = 0;
            switch(dir) {
                case WEST:
                case EAST:
                    lasers[i].w = 2;
                    lasers[i].h = 1;
                    DrawMap(lasers[i].x, lasers[i].y, mapLaserHorizontal[lasers[i].tileIndex]);
                    break;
                default:
                    lasers[i].w = 1;
                    lasers[i].h = 2;
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
        LaserDeactivate(i);
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

    Fill(lasers[i].x, lasers[i].y, lasers[i].w, lasers[i].h, 0);
    switch(lasers[i].dir) {
        case WEST:
            lasers[i].y--;
            DrawMap(lasers[i].x, lasers[i].y, mapLaserHorizontal[lasers[i].tileIndex]);
            break;
        case EAST:
            lasers[i].y++;
            DrawMap(lasers[i].x, lasers[i].y, mapLaserHorizontal[lasers[i].tileIndex]);
            break;
        case NORTH:
            lasers[i].x++;
            DrawMap(lasers[i].x, lasers[i].y, mapLaserVertical[lasers[i].tileIndex]);
            break;
        default:
            lasers[i].x--;
            DrawMap(lasers[i].x, lasers[i].y, mapLaserVertical[lasers[i].tileIndex]);
    }
}

void LaserDeactivate(u8 i) {
    Fill(lasers[i].x, lasers[i].y, lasers[i].w, lasers[i].h, 0);
    lasers[i].active = 0;
}