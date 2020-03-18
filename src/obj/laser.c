#include "laser.h"

Laser lasers[LASER_COUNT];
Laser lasersEnemy[LASER_COUNT_ENEMY];

void LaserUpdateTileIndex(u8);

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

    // Backfeed vs forward
    if(lasers[i].backfeed && lasers[i].time > 0) {
        lasers[i].time -= 2;
    } else {
        lasers[i].time += 2;
    }

    // Lasers
    if(lasers[i].time == 20) {
        LaserDeactivate(i);
        return;
    } else if(lasers[i].time < 4) {
        LaserUpdateTileIndex(i);
    } else if(lasers[i].time < 16) {
        if(lasers[i].time % 4 == 0) {
            LaserUpdateTileIndex(i);
        }
    } else {
        if(lasers[i].time % 2 == 0) {
            LaserUpdateTileIndex(i);
        }
    }

    // Don't update if it's not a multiple of 2
    if(lasers[i].time % 2) {
        return;
    }

    Fill(lasers[i].x, lasers[i].y, lasers[i].w, lasers[i].h, 0);
    switch(lasers[i].dir) {
        case WEST:
            if(lasers[i].backfeed) {
                if(lasers[i].y == EDGE_WEST) {
                    LaserEnemyDeactivate(i);
                } else {
                    lasers[i].y++;
                    DrawMap(lasers[i].x, lasers[i].y, mapLaserBackfeedHorizontal[lasers[i].tileIndex]);
                }
            } else {
                lasers[i].y--;
                DrawMap(lasers[i].x, lasers[i].y, mapLaserHorizontal[lasers[i].tileIndex]);
            }
            break;
        case EAST:
            if(lasers[i].backfeed) {
                if(lasers[i].y == EDGE_EAST) {
                    LaserEnemyDeactivate(i);
                } else {
                    lasers[i].y--;
                    DrawMap(lasers[i].x, lasers[i].y, mapLaserBackfeedHorizontal[lasers[i].tileIndex]);
                }
            } else {
                lasers[i].y++;
                DrawMap(lasers[i].x, lasers[i].y, mapLaserHorizontal[lasers[i].tileIndex]);
            }
            break;
        case NORTH:
            if(lasers[i].backfeed) {
                if(lasers[i].y == EDGE_NORTH) {
                    LaserEnemyDeactivate(i);
                } else {
                    lasers[i].x--;
                    DrawMap(lasers[i].x, lasers[i].y, mapLaserBackfeedVertical[lasers[i].tileIndex]);
                }
            } else {
                lasers[i].x++;
                DrawMap(lasers[i].x, lasers[i].y, mapLaserVertical[lasers[i].tileIndex]);
            }
            break;
        default:
            if(lasers[i].backfeed) {
                if(lasers[i].y == EDGE_SOUTH) {
                    LaserEnemyDeactivate(i);
                } else {
                    lasers[i].x++;
                    DrawMap(lasers[i].x, lasers[i].y, mapLaserBackfeedVertical[lasers[i].tileIndex]);
                }
            } else {
                lasers[i].x--;
                DrawMap(lasers[i].x, lasers[i].y, mapLaserVertical[lasers[i].tileIndex]);
            }
    }
}

void LaserUpdateTileIndex(u8 i) {
    if(lasers[i].backfeed) {
        lasers[i].tileIndex += lasers[i].tileIndex ? -1 : 0;
    } else {
        lasers[i].tileIndex++;
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
                lasersEnemy[i].y++;
                DrawMap(lasersEnemy[i].x, lasersEnemy[i].y, mapEnemyLaserHorizontal);
            }
            break;
        case EAST:
            if(lasersEnemy[i].y == EDGE_EAST) {
                LaserEnemyDeactivate(i);
            } else {
                lasersEnemy[i].y--;
                DrawMap(lasersEnemy[i].x, lasersEnemy[i].y, mapEnemyLaserHorizontal);
            }
            break;
        case NORTH:
            if(lasersEnemy[i].y == EDGE_NORTH) {
                LaserEnemyDeactivate(i);
            } else {
                lasersEnemy[i].x--;
                DrawMap(lasersEnemy[i].x, lasersEnemy[i].y, mapEnemyLaserVertical);
            }
            break;
        default:
            if(lasersEnemy[i].y == EDGE_SOUTH) {
                LaserEnemyDeactivate(i);
            } else {
                lasersEnemy[i].x++;
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
