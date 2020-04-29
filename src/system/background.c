#include "background.h"

u8 bgCrossX[BACKGROUND_CROSS_COUNT], bgCrossY[BACKGROUND_CROSS_COUNT];
u8 updateTime;

void BackgroundStart() {
    bgCrossX[0] = 13;
    bgCrossY[0] = 11;

    bgCrossX[1] = 18;
    bgCrossY[1] = 11;

    bgCrossX[2] = 18;
    bgCrossY[2] = 16;

    bgCrossX[3] = 13;
    bgCrossY[3] = 16;

    bgCrossX[4] = 7;
    bgCrossY[4] = 5;

    bgCrossX[5] = 24;
    bgCrossY[5] = 5;

    bgCrossX[6] = 24;
    bgCrossY[6] = 22;

    bgCrossX[7] = 7;
    bgCrossY[7] = 22;

    u8 i = BACKGROUND_CROSS_COUNT;
    while(i--) {
        DrawMap(bgCrossX[i], bgCrossY[i], i % 2 ? mapBGCrossA : mapBGCrossB);
    }

    updateTime = 0;
}

void BackgroundUpdate() {
    updateTime++;
    if(updateTime == 3) {
        updateTime = 0;
    } else {
        return;
    }

    u8 i = BACKGROUND_CROSS_COUNT;
    u8 prevTile, nextTile;
    while(i--) {
        // Only erase tile if it's a true BG "star"
        prevTile = GetTile(bgCrossX[i], bgCrossY[i]);
        if(prevTile == pgm_read_byte(&(mapBGCrossA[2])) || prevTile == pgm_read_byte(&(mapBGCrossB[2]))) {
            SetTile(bgCrossX[i], bgCrossY[i], 0);
        }

        // Map the next Y position
        switch(i) {
            case 0:
            case 1:
            case 4:
            case 5:
                bgCrossY[i] = bgCrossY[i] == 0 ? 11 : bgCrossY[i] - 1;
                break;
            default:
                bgCrossY[i] = bgCrossY[i] == 27 ? 16 : bgCrossY[i] + 1;
        }

        // Map the next X position
        switch(i) {
            case 1:
            case 2:
            case 5:
            case 6:
                bgCrossX[i] = bgCrossX[i] == 29 ? 18 : bgCrossX[i] + 1;
                break;
            default:
                bgCrossX[i] = bgCrossX[i] == 2 ? 13 : bgCrossX[i] - 1;
        }

        // Only write tile if it's blank
        nextTile = GetTile(bgCrossX[i], bgCrossY[i]);
        if(nextTile == 0) {
            DrawMap(bgCrossX[i], bgCrossY[i], i % 2 ? mapBGCrossB : mapBGCrossA);
        }
    }
}
