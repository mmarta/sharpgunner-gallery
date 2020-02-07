#ifndef PLAYER_H
#define PLAYER_H

#include "../system/defines.h"
#include "../system/graphics.h"
#include "laser.h"

#define PLAYER_COUNT 2
#define PLAYER_SHIP_SPRITE_ID 0
#define PLAYER_SHIP_WIDTH 2
#define PLAYER_SHIP_HEIGHT 2
#define PLAYER_XHAIR_SPRITE_ID 4
#define PLAYER_XHAIR_WIDTH 2
#define PLAYER_XHAIR_HEIGHT 2

typedef struct {
    u8 lives, animationTime, firing, poweredUp, x, y, dir;
    u16 scoreDelta;
    u32 score;
} Player;

extern Player players[];
extern u8 activePlayer;

void PlayerStart(u8);
void PlayerAddScoreDelta(u16);
void PlayerFlushScore();
void PlayerFire();
void PlayerResume();
void PlayerInput();
void PlayerUpdate();

#endif