#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "defines.h"

#define U32_MAX 0xffffffff

extern const char mapFighterSouthA[];
extern const char mapFighterSouthB[];
extern const char mapFighterSouthC[];
extern const char mapFighterWestA[];
extern const char mapFighterWestB[];
extern const char mapFighterWestC[];
extern const char mapFighterNorthA[];
extern const char mapFighterNorthB[];
extern const char mapFighterNorthC[];
extern const char mapFighterEastA[];
extern const char mapFighterEastB[];
extern const char mapFighterEastC[];

extern const char mapLaserVerticalA[];
extern const char mapLaserVerticalB[];
extern const char mapLaserVerticalC[];
extern const char mapLaserVerticalD[];
extern const char mapLaserVerticalE[];
extern const char mapLaserVerticalF[];
extern const char mapLaserVerticalG[];
extern const char mapLaserVerticalH[];

extern const char mapLaserHorizontalA[];
extern const char mapLaserHorizontalB[];
extern const char mapLaserHorizontalC[];
extern const char mapLaserHorizontalD[];
extern const char mapLaserHorizontalE[];
extern const char mapLaserHorizontalF[];
extern const char mapLaserHorizontalG[];
extern const char mapLaserHorizontalH[];

extern const char *mapFighterA[];
extern const char *mapFighterB[];
extern const char *mapFighterC[];

extern const char *mapLaserVertical[];
extern const char *mapLaserHorizontal[];

extern const char tiles[];

void PrintVerticalPROGMEM(u8, u8, const char *);
void PrintVerticalRAM(u8, u8, const char *);
void PrintU8Vertical(u8, u8, u8);
void PrintU32Vertical(u8, u8, u32, u32);
void HideSprite(u8, u8, u8);

#endif