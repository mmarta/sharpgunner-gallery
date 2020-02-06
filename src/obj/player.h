#ifndef PLAYER_H
#define PLAYER_H

#include "../system/defines.h"
#include "../system/graphics.h"
#include "bullet.h"

#define PLAYER_COUNT 2
#define PLAYER_SHIP_SPRITE_ID 0
#define PLAYER_SHIP_W 2
#define PLAYER_SHIP_H 2
#define PLAYER_XHAIR_SPRITE_ID 4
#define PLAYER_XHAIR_W 2
#define PLAYER_XHAIR_H 2

typedef struct {
    u8 lives, animationTime, firing, poweredUp;
    u32 score;
} Player;

extern Player players[];
extern u8 activePlayer;

void PlayerStart(u8);
void PlayerFire();
void PlayerResume();
void PlayerInput();
void PlayerUpdate();

#endif