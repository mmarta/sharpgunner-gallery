#ifndef _MACHINE_H
#define _MACHINE_H

#include "defines.h"
#include "graphics.h"
#include "../audio/sfx.h"

typedef enum {
    GAME, TITLE
} MachineMode;

extern u8 credits;
extern MachineMode machineMode;
extern u32 hi;
extern int inputs[];

void MachineSetup();
void MachineCrossHatch();
void MachineInitHi();
void MachineInput();

#endif
