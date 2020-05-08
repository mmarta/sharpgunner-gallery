#ifndef _MACHINE_H
#define _MACHINE_H

#include "defines.h"
#include "graphics.h"
#include "../audio/audio.h"

#define EEPROM_BLOCK 10

typedef enum {
    GAME, TITLE, TEST
} MachineMode;

extern u8 credits;
extern MachineMode machineMode;
extern u32 hi;
extern int inputs[];

extern u8 coinsPerPlay, controllers, attractSound;

void MachineSetup();
void MachineCrossHatch();
void MachineInitHi();
u8 MachineInput();

#endif
