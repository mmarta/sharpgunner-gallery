#include "audio.h"

const struct PatchStruct patches[] PROGMEM = {
    {0, NULL, patchCoinUp, 0, 0},
    {0, NULL, patchPlayerFire, 0, 0},
    {0, NULL, patchPlayerLaunchHook, 0, 0},
    {0, NULL, patchPlayerLatchHook, 0, 0},
    {0, NULL, patchNextLevel, 0, 0},
    {0, NULL, patchPlayerKill, 0, 0},
    {0, NULL, patchEnemyKill, 0, 0},
    {0, NULL, patchTink, 0, 0},
    {0, NULL, patchExtend, 0, 0},
    {0, NULL, patchBackfire, 0, 0},
    {0, NULL, patchBG, 0, 0},
    {0, NULL, musicPatchStartA, 0, 0},
    {0, NULL, musicPatchStartB, 0, 0},
    {0, NULL, musicPatchGameOverA, 0, 0},
    {0, NULL, musicPatchGameOverB, 0, 0}
};

void AudioInit() {
    EnableSoundEngine();
    InitMusicPlayer(patches);
}
