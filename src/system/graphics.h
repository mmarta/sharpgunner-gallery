#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "defines.h"

#define U32_MAX 0xffffffff

extern const char mapFighterSouthA[];
extern const char mapFighterSouthB[];
extern const char mapFighterSouthC[];

extern const char mapLaserSouthA[];
extern const char mapLaserSouthB[];
extern const char mapLaserSouthC[];
extern const char mapLaserSouthD[];

extern const char *mapLaserSouth[];

extern const char tiles[];

void PrintVerticalPROGMEM(u8, u8, const char *);
void PrintVerticalRAM(u8, u8, const char *);
void PrintU8Vertical(u8, u8, u8);
void PrintU32Vertical(u8, u8, u32, u32);
void HideSprite(u8, u8, u8);

#endif