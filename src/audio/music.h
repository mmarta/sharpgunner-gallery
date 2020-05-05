#ifndef _MUSIC_H
#define _MUSIC_H

#include "sfx.h"

#define MUSIC_START 10

extern const char musicPatchStartA[];
extern const char musicPatchStartB[];

void MusicPlayPatch(u8 musicNum);

#endif
