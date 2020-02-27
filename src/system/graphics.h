#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "defines.h"

#define U32_MAX 0xffffffff

// The created tilemaps

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

extern const char mapFighterKillA[];
extern const char mapFighterKillB[];
extern const char mapFighterKillC[];
extern const char mapFighterKillD[];

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

extern const char mapInvaderSouthA[];
extern const char mapInvaderWestA[];
extern const char mapInvaderNorthA[];
extern const char mapInvaderEastA[];
extern const char mapInvaderSouthB[];
extern const char mapInvaderWestB[];
extern const char mapInvaderNorthB[];
extern const char mapInvaderEastB[];

extern const char mapEnemyKillA[];
extern const char mapEnemyKillB[];
extern const char mapEnemyKillC[];
extern const char mapEnemyKillD[];

extern const char mapInvaderWarnSouth[];
extern const char mapInvaderWarnWest[];
extern const char mapInvaderWarnNorth[];
extern const char mapInvaderWarnEast[];

extern const char mapSweeperSouthA[];
extern const char mapSweeperWestA[];
extern const char mapSweeperNorthA[];
extern const char mapSweeperEastA[];
extern const char mapSweeperSouthB[];
extern const char mapSweeperWestB[];
extern const char mapSweeperNorthB[];
extern const char mapSweeperEastB[];

extern const char mapHookNE[];
extern const char mapHookSE[];
extern const char mapHookSW[];
extern const char mapHookNW[];
extern const char mapWireA[];
extern const char mapWireB[];

// Progression Maps (arrays of pointers)

extern const char *mapFighterA[];
extern const char *mapFighterB[];
extern const char *mapFighterC[];
extern const char *mapFighterKill[];

extern const char *mapLaserVertical[];
extern const char *mapLaserHorizontal[];

extern const char *mapInvaderA[];
extern const char *mapInvaderB[];
extern const char *mapInvaderWarn[];

extern const char *mapSweeperA[];
extern const char *mapSweeperB[];

extern const char *mapEnemyKill[];

// The bare tiles themselves

extern const char tiles[];

void PrintVerticalPROGMEM(u8, u8, const char *);
void PrintVerticalRAM(u8, u8, const char *);
void PrintU8Vertical(u8, u8, u8);
void PrintU32Vertical(u8, u8, u32, u32);

#endif
