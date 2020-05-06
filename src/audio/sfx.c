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
    0, PC_WAVE, 3,
    0, PC_ENV_VOL, 192,
    0, PC_PITCH, 80,
    0, PC_SLIDE, -20,
    3, PC_ENV_VOL, 127,
    0, PC_NOTE_DOWN, 22,
    0, PC_SLIDE, 50,
    0, PC_ENV_VOL, 80,
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

const char patchPlayerKill[] PROGMEM = {
    0, PC_WAVE, 4,
    0, PC_PITCH, 30,
    0, PC_SLIDE, -30,
    6, PC_ENV_VOL, 192,
    0, PC_PITCH, 30,
    0, PC_SLIDE, -30,
    6, PC_ENV_VOL, 128,
    0, PC_PITCH, 30,
    0, PC_SLIDE, -30,
    6, PC_ENV_VOL, 64,
    0, PC_PITCH, 30,
    0, PC_SLIDE, -30,
    6, PC_NOTE_CUT, 0,
    0, PATCH_END
};

const char patchEnemyKill[] PROGMEM = {
    0, PC_WAVE, 5,
    0, PC_PITCH, 40,
    0, PC_SLIDE, 40,
    2, PC_ENV_VOL, 192,
    2, PC_ENV_VOL, 128,
    2, PC_ENV_VOL, 64,
    0, PC_PITCH, 50,
    0, PC_SLIDE, 40,
    2, PC_ENV_VOL, 192,
    2, PC_ENV_VOL, 128,
    2, PC_ENV_VOL, 64,
    2, PC_NOTE_CUT, 0,
    0, PATCH_END
};

const char patchBackfire[] PROGMEM = {
    0, PC_WAVE, 5,
    0, PC_PITCH, 48,
    2, PC_PITCH, 54,
    2, PC_PITCH, 48,
    2, PC_PITCH, 54,
    2, PC_PITCH, 48,
    2, PC_PITCH, 54,
    2, PC_PITCH, 48,
    2, PC_PITCH, 54,
    2, PC_NOTE_CUT, 0,
    0, PATCH_END
};

const char patchTink[] PROGMEM = {
    0, PC_WAVE, 3,
    0, PC_PITCH, 108,
    1, PC_ENV_VOL, 192,
    1, PC_ENV_VOL, 128,
    1, PC_ENV_VOL, 64,
    1, PC_ENV_VOL, 32,
    1, PC_NOTE_CUT, 0,
    0, PATCH_END
};

const char patchExtend[] PROGMEM = {
    0, PC_WAVE, 4,
    0, PC_PITCH, 72,
    6, PC_NOTE_UP, 7,
    6, PC_NOTE_DOWN, 3,
    6, PC_NOTE_UP, 8,
    4, PC_ENV_VOL, 192,
    4, PC_ENV_VOL, 128,
    4, PC_ENV_VOL, 64,
    4, PC_ENV_VOL, 32,
    4, PC_NOTE_CUT, 0,
    0, PATCH_END
};

const char patchBG[] PROGMEM = {
    0, PC_WAVE, 2,
    0, PC_PITCH, 40,
    0, PC_ENV_VOL, 192,
    0, PC_SLIDE, -10,
    20, PC_NOTE_CUT, 0,
    0, PATCH_END
};

void SFXPlay(u8 patchNum) {
    TriggerFx(patchNum, 192, 1);
}
