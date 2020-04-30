#include "sfx.h"

const char patchCoinUp[] PROGMEM = {
    0, PC_WAVE, 4,
    0, PC_ENV_SPEED, -20,
    0, PC_PITCH, 79,
    6, PC_NOTE_UP, 5,
    6, PC_NOTE_CUT, 0,
    0, PATCH_END
};

const char patchPlayerFire[] PROGMEM = {
    0, PC_WAVE, 7,
    0, PC_PITCH, 48,
    0, PC_SLIDE, -20,
    4, PC_ENV_VOL, 127,
    2, PC_ENV_VOL, 80,
    2, PC_NOTE_CUT, 0,
    0, PATCH_END
};

const char patchPlayerLaunchHook[] PROGMEM = {
    0, PC_WAVE, 1,
    0, PC_PITCH, 81,
    0, PC_SLIDE, -50,
    2, PC_ENV_VOL, 127,
    0, PC_SLIDE, -50,
    2, PC_ENV_VOL, 80,
    0, PC_SLIDE, -50,
    2, PC_NOTE_CUT, 0,
    0, PATCH_END
};

const char patchPlayerLatchHook[] PROGMEM = {
    0, PC_WAVE, 3,
    0, PC_PITCH, 95,
    0, PC_SLIDE, -50,
    1, PC_PITCH, 110,
    0, PC_ENV_VOL, 127,
    1, PC_NOTE_CUT, 0,
    0, PATCH_END
};

const char patchNextLevel[] PROGMEM = {
    0, PC_WAVE, 3,
    0, PC_PITCH, 60,
    4, PC_NOTE_UP, 6,
    4, PC_NOTE_UP, 6,
    4, PC_NOTE_UP, 6,
    0, PC_ENV_VOL, 180,
    4, PC_PITCH, 60,
    4, PC_NOTE_UP, 6,
    4, PC_NOTE_UP, 6,
    4, PC_NOTE_UP, 6,
    0, PC_ENV_VOL, 110,
    4, PC_PITCH, 60,
    4, PC_NOTE_UP, 6,
    4, PC_NOTE_UP, 6,
    4, PC_NOTE_UP, 6,
    4, PC_NOTE_CUT, 0,
    0, PATCH_END
};

const struct PatchStruct patches[] PROGMEM = {
    {0, NULL, patchCoinUp, 0, 0},
    {0, NULL, patchPlayerFire, 0, 0},
    {0, NULL, patchPlayerLaunchHook, 0, 0},
    {0, NULL, patchPlayerLatchHook, 0, 0},
    {0, NULL, patchNextLevel, 0, 0}
};

void SFXInit() {
    InitMusicPlayer(patches);
}
