#ifndef _TITLE_H
#define _TITLE_H

#include "../system/defines.h"
#include "../system/graphics.h"
#include "../system/machine.h"
#include "../obj/player.h"
#include "game.h"

extern u16 titleTime;

void TitleStart();
void TitleUpdate();

#define CLEAR_TITLE() Fill(2, 0, 29, 28, 0)

#endif
