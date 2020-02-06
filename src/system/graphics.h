#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "defines.h"

#define U32_MAX 0xffffffff
            
extern const char spriteMapCrosshair[];
extern const char spriteMapCrosshairTarget[];
extern const char spriteMapSharpgunnerA[];
extern const char spriteMapSharpgunnerB[];
extern const char spriteMapSharpgunnerC[];

extern const char spriteMapBulletA[];
extern const char spriteMapBulletB[];
extern const char spriteMapBulletC[];
extern const char spriteMapBulletD[];

extern const char bgFontTiles[];
extern const char spriteTiles[];

void PrintVerticalPROGMEM(u8, u8, const char *);
void PrintVerticalRAM(u8, u8, const char *);
void PrintU8Vertical(u8, u8, u8);
void PrintU32Vertical(u8, u8, u32, u32);
void HideSprite(u8, u8, u8);

#endif