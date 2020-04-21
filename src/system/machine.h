#ifndef _MACHINE_H
#define _MACHINE_H

#include "defines.h"
#include "graphics.h"

typedef enum {
    GAME, TITLE
} MachineMode;

extern u8 credits;
extern MachineMode machineMode;
extern u32 hi;

void MachineSetup();
void MachineInput();

#endif
