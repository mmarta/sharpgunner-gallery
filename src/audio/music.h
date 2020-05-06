#ifndef _MUSIC_H
#define _MUSIC_H

#include "sfx.h"

#define MUSIC_START 11
#define MUSIC_GAME_OVER 13

extern const char musicPatchStartA[];
extern const char musicPatchStartB[];
extern const char musicPatchGameOverA[];
extern const char musicPatchGameOverB[];

void MusicPlayPatch(u8 musicNum);

#endif
