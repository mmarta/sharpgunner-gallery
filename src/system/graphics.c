#include "graphics.h"

#include "../../gfxdata/tiles.inc"

const char *mapFighterA[] = {
    mapFighterSouthA, mapFighterWestA,
    mapFighterNorthA, mapFighterEastA
};

const char *mapFighterB[] = {
    mapFighterSouthB, mapFighterWestB,
    mapFighterNorthB, mapFighterEastB
};

const char *mapFighterC[] = {
    mapFighterSouthC, mapFighterWestC,
    mapFighterNorthC, mapFighterEastC
};

const char *mapFighterKill[] = {
    mapFighterKillA, mapFighterKillB,
    mapFighterKillC, mapFighterKillD
};

const char *mapLaserVertical[] = {
    mapLaserVerticalA, mapLaserVerticalB,
    mapLaserVerticalC, mapLaserVerticalD,
    mapLaserVerticalE, mapLaserVerticalF,
    mapLaserVerticalG, mapLaserVerticalH
};

const char *mapLaserHorizontal[] = {
    mapLaserHorizontalA, mapLaserHorizontalB,
    mapLaserHorizontalC, mapLaserHorizontalD,
    mapLaserHorizontalE, mapLaserHorizontalF,
    mapLaserHorizontalG, mapLaserHorizontalH
};

const char *mapInvaderA[] = {
    mapInvaderSouthA, mapInvaderWestA,
    mapInvaderNorthA, mapInvaderEastA
};

const char *mapInvaderB[] = {
    mapInvaderSouthB, mapInvaderWestB,
    mapInvaderNorthB, mapInvaderEastB
};

const char *mapEnemyKill[] = {
    mapEnemyKillA, mapEnemyKillB,
    mapEnemyKillC, mapEnemyKillD
};

const char *mapInvaderWarn[] = {
    mapInvaderWarnSouth, mapInvaderWarnWest,
    mapInvaderWarnNorth, mapInvaderWarnEast
};

void PrintVerticalPROGMEM(u8 x, u8 y, const char *str) {
    u8 i = 0, c = pgm_read_byte(&(str[i]));
    while(c) {
        SetTile(x, y--, c - 32);
        c = pgm_read_byte(&(str[++i]));
    }
}

void PrintVerticalRAM(u8 x, u8 y, const char *str) {
    u8 i = 0;
    while(str[i]) {
        SetTile(x, y--, str[i] - 32);
        i++;
    }
}

void PrintU8Vertical(u8 x, u8 y, u8 val) {
    u8 max = 0xff, first = 1, modVal;

    do {
        modVal = val % 10;
        SetTile(x, y++, !first && modVal == 0 && val == 0 ? 0 : modVal + 16);
        val /= 10;
        max /= 10;
        first = 0;
    } while(max > 0);
}

void PrintU32Vertical(u8 x, u8 y, u32 val, u32 maxVal) {
    u8 first = 1, modVal;

    do {
        modVal = val % 10;
        SetTile(x, y++, !first && modVal == 0 && val == 0 ? 0 : modVal + 16);
        val /= 10;
        maxVal /= 10;
        first = 0;
    } while(maxVal > 0);
}
