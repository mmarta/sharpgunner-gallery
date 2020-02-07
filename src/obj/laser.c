#include "laser.h"

Laser laser;

void LaserInit(u8 dir) {
    if(!laser.active) {
        laser.dir = dir;
        laser.x = LASER_SOUTH_START_X;
        laser.y = LASER_SOUTH_START_Y;
        laser.time = 0;
        DrawMap(laser.x, laser.y, mapLaserSouth[laser.time]);
        laser.active = 1;
    }
}

void LaserUpdate() {
    if(!laser.active) {
        return;
    }

    laser.time++;

    switch(laser.dir) {
        default:
            Fill(laser.x, laser.y, 1, 2, 0);
            if(laser.time == 6) {
                laser.active = 0;
                return;
            }
            laser.x--;
            DrawMap(laser.x, laser.y, mapLaserSouth[laser.time]);
    }
}