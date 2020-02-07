#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "defines.h"

#define U32_MAX 0xffffffff

extern const char mapFighterSouthA[];
extern const char mapFighterSouthB[];
extern const char mapFighterSouthC[];

extern const char mapBulletBigA[];
extern const char mapBulletBigB[];
extern const char mapBulletBigC[];
extern const char mapBulletBigD[];
extern const char mapBulletBigE[];

extern const char mapBulletSmallA[];
extern const char mapBulletSmallB[];
extern const char mapBulletSmallC[];
extern const char mapBulletSmallD[];
extern const char mapBulletSmallE[];
extern const char mapBulletSmallF[];
extern const char mapBulletSmallG[];
extern const char mapBulletSmallH[];
extern const char mapBulletSmallI[];
extern const char mapBulletSmallJ[];
extern const char mapBulletSmallK[];
extern const char mapBulletSmallL[];

extern const char *mapBulletSouth[];

extern const char tiles[];

void PrintVerticalPROGMEM(u8, u8, const char *);
void PrintVerticalRAM(u8, u8, const char *);
void PrintU8Vertical(u8, u8, u8);
void PrintU32Vertical(u8, u8, u32, u32);
void HideSprite(u8, u8, u8);

#endif