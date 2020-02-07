#include "graphics.h"

#include "../../gfxdata/tiles.inc"

const char *mapBulletSouth[] = {
    mapBulletSouthH, mapBulletSouthG,
    mapBulletSouthF, mapBulletSouthE,
    mapBulletSouthD, mapBulletSouthC,
    mapBulletSouthB, mapBulletSouthA
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

void HideSprite(u8 id, u8 w, u8 h) {
    w *= h;
    w += id;
    while(w-- > id) {
        sprites[w].y = 224;
    }
}