#ifndef _TEST_H
#define _TEST_H

#include "../system/defines.h"
#include "../system/graphics.h"
#include "../system/machine.h"

typedef enum {
    OPTION_COINS, OPTION_CONTROLS, OPTION_ATTRACT_SOUND, OPTION_LIVES, OPTION_EXIT
} testoption;

void TestInit();
void TestUpdate();

#endif
