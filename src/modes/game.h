#ifndef _GAME_H
#define _GAME_H

#include "../system/defines.h"
#include "../system/graphics.h"
#include "../system/machine.h"
#include "../system/background.h"
#include "../obj/laser.h"
#include "../obj/player.h"
#include "../obj/enemy.h"
#include "../obj/collision.h"
#include "../system/level.h"
#include "../system/enemygen.h"

void GameStart(u8);
void GameUpdate();

#endif
