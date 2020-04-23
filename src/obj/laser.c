#include "laser.h"

Laser lasers[LASER_COUNT];

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
                    LaserDeactivate(i);
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
                    LaserDeactivate(i);
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
                if(lasers[i].x == EDGE_NORTH) {
                    LaserDeactivate(i);
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
                if(lasers[i].x == EDGE_SOUTH) {
                    LaserDeactivate(i);
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

void LaserDeactivate(u8 i) {
    if(lasers[i].active) {
        Fill(lasers[i].x, lasers[i].y, lasers[i].w, lasers[i].h, 0);
        lasers[i].active = 0;
    }
}
