#ifndef _ENEMYGEN_H
#define _ENEMYGEN_H

#include "defines.h"
#include "level.h"
#include "../obj/player.h"
#include "../obj/enemy.h"

extern u8 enemyGenSpawnTimeout;

void EnemyGenLevelBegin();
void EnemyGenEngineTick();

#endif
