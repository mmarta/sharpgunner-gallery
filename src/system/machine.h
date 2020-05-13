#ifndef _MACHINE_H
#define _MACHINE_H

#include "defines.h"
#include "graphics.h"
#include "../audio/audio.h"

#define EEPROM_BLOCK 10

typedef enum {
    GAME, TITLE, TEST
} machinemode;

typedef enum {
    DOWN, DOWN_LEFT, LEFT, UP_LEFT,
    UP, UP_RIGHT, RIGHT, DOWN_RIGHT
} stickpos;

extern u8 credits;
extern machinemode machineMode;
extern u32 hi;
extern int inputs[];

extern u8 coinsPerPlay, controllers, attractSound, livesPerPlay;

void MachineSetup();
void MachineCrossHatch();
void MachineInitHi();
u8 MachineInput();

#endif
