#ifndef _SFX_H
#define _SFX_H

#include "../system/defines.h"

#define PATCH_COIN_UP 0
#define PATCH_PLAYER_FIRE 1
#define PATCH_PLAYER_LAUNCH_HOOK 2
#define PATCH_PLAYER_LATCH_HOOK 3
#define PATCH_NEXT_LEVEL 4
#define PATCH_PLAYER_KILL 5
#define PATCH_ENEMY_KILL 6
#define PATCH_TINK 7
#define PATCH_EXTEND 8
#define PATCH_BACKFIRE 9

extern const struct PatchStruct patches[];

void SFXInit();
void SFXPlay(u8);

#endif
