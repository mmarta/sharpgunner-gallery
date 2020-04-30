#ifndef _SFX_H
#define _SFX_H

#include "../system/defines.h"

#define PATCH_COIN_UP 0
#define PATCH_PLAYER_FIRE 1
#define PATCH_PLAYER_LAUNCH_HOOK 2
#define PATCH_PLAYER_LATCH_HOOK 3
#define PATCH_NEXT_LEVEL 4

extern const struct PatchStruct patches[];

void SFXInit();

#endif
