#include "laser.h"

Laser lasers[LASER_COUNT];
Laser lasersEnemy[LASER_COUNT_ENEMY];

u8 LaserInit(direction dir, u8 x, u8 y) {
    u8 i = LASER_COUNT;

    while(i--) {
        if(!lasers[i].active) {
            lasers[i].dir = dir;
            lasers[i].x = x;
            lasers[i].y = y;
            lasers[i].time = 0;
            lasers[i].tileIndex = 0;
            lasers[i].backfeed = false;

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

u8 LaserEnemyInit(direction dir, u8 x, u8 y) {
    u8 i = LASER_COUNT;

    while(i--) {
        if(!lasersEnemy[i].active) {
            lasersEnemy[i].dir = dir;
            lasersEnemy[i].x = x;
            lasersEnemy[i].y = y;
            lasersEnemy[i].time = 0;
            lasersEnemy[i].tileIndex = 0;
            lasersEnemy[i].backfeed = false;
            lasersEnemy[i].w = 2;
            lasersEnemy[i].h = 2;

            switch(dir) {
                case WEST:
                case EAST:
                    DrawMap(lasersEnemy[i].x, lasersEnemy[i].y, mapEnemyLaserHorizontal);
                    break;
                default:
                    DrawMap(lasersEnemy[i].x, lasersEnemy[i].y, mapEnemyLaserVertical);
            }

            lasersEnemy[i].active = 1;
            return 1;
        }
    }

    return 0;
}

void LaserUpdate(u8 i) {
    if(!lasers[i].active) {
        return;
    }

    if(lasers[i].backfeed) {
        lasers[i].time -= 2;
    } else {
        lasers[i].time += 2;
    }

    if(lasers[i].time == 20 || !lasers[i].time) {
        LaserDeactivate(i);
        return;
    } else if(lasers[i].time < 4) {
        if(lasers[i].time % 2 == 0) {
            lasers[i].tileIndex += lasers[i].backfeed ? -1 : 1;
        }
    } else if(lasers[i].time < 16) {
        if(lasers[i].time % 4 == 0) {
            lasers[i].tileIndex += lasers[i].backfeed ? -1 : 1;
        }
    } else {
        if(lasers[i].time % 2 == 0) {
            lasers[i].tileIndex += lasers[i].backfeed ? -1 : 1;
        }
    }

    if(lasers[i].time % 2) {
        return;
    }

    Fill(lasers[i].x, lasers[i].y, lasers[i].w, lasers[i].h, 0);
    switch(lasers[i].dir) {
        case WEST:
            lasers[i].y -= lasers[i].backfeed ? -1 : 1;
            DrawMap(lasers[i].x, lasers[i].y, lasers[i].backfeed ? mapLaserBackfeedHorizontal[lasers[i].tileIndex] : mapLaserHorizontal[lasers[i].tileIndex]);
            break;
        case EAST:
            lasers[i].y += lasers[i].backfeed ? -1 : 1;
            DrawMap(lasers[i].x, lasers[i].y, lasers[i].backfeed ? mapLaserBackfeedHorizontal[lasers[i].tileIndex] : mapLaserHorizontal[lasers[i].tileIndex]);
            break;
        case NORTH:
            lasers[i].x += lasers[i].backfeed ? -1 : 1;
            DrawMap(lasers[i].x, lasers[i].y, lasers[i].backfeed ? mapLaserBackfeedVertical[lasers[i].tileIndex]: mapLaserVertical[lasers[i].tileIndex]);
            break;
        default:
            lasers[i].x -= lasers[i].backfeed ? -1 : 1;
            DrawMap(lasers[i].x, lasers[i].y, lasers[i].backfeed ? mapLaserBackfeedVertical[lasers[i].tileIndex]: mapLaserVertical[lasers[i].tileIndex]);
    }
}

void LaserEnemyUpdate(u8 i) {
    if(!lasersEnemy[i].active) {
        return;
    }

    lasersEnemy[i].time++;
    if(lasersEnemy[i].time % 4) {
        return;
    }

    Fill(lasersEnemy[i].x, lasersEnemy[i].y, lasersEnemy[i].w, lasersEnemy[i].h, 0);
    switch(lasersEnemy[i].dir) {
        case WEST:
            if(lasersEnemy[i].y == EDGE_WEST) {
                LaserEnemyDeactivate(i);
            } else {
                lasersEnemy[i].y += 1;
                DrawMap(lasersEnemy[i].x, lasersEnemy[i].y, mapEnemyLaserHorizontal);
            }
            break;
        case EAST:
            if(lasersEnemy[i].y == EDGE_EAST) {
                LaserEnemyDeactivate(i);
            } else {
                lasersEnemy[i].y -= 1;
                DrawMap(lasersEnemy[i].x, lasersEnemy[i].y, mapEnemyLaserHorizontal);
            }
            break;
        case NORTH:
            if(lasersEnemy[i].y == EDGE_NORTH) {
                LaserEnemyDeactivate(i);
            } else {
                lasersEnemy[i].x -= 1;
                DrawMap(lasersEnemy[i].x, lasersEnemy[i].y, mapEnemyLaserVertical);
            }
            break;
        default:
            if(lasersEnemy[i].y == EDGE_SOUTH) {
                LaserEnemyDeactivate(i);
            } else {
                lasersEnemy[i].x += 1;
                DrawMap(lasersEnemy[i].x, lasersEnemy[i].y, mapEnemyLaserVertical);
            }
    }
}

void LaserDeactivate(u8 i) {
    Fill(lasers[i].x, lasers[i].y, lasers[i].w, lasers[i].h, 0);
    lasers[i].active = 0;
}

void LaserEnemyDeactivate(u8 i) {
    Fill(lasersEnemy[i].x, lasersEnemy[i].y, lasersEnemy[i].w, lasersEnemy[i].h, 0);
    lasersEnemy[i].active = 0;
}
