#ifndef PLAYER_H
#define PLAYER_H

#include "../system/defines.h"
#include "../system/graphics.h"
#include "laser.h"

#define PLAYER_COUNT 2
#define PLAYER_WIDTH 2
#define PLAYER_HEIGHT 2

#define PLAYER_SOUTH_X 28
#define PLAYER_SOUTH_Y 13
#define PLAYER_WEST_X 15
#define PLAYER_WEST_Y 26
#define PLAYER_NORTH_X 2
#define PLAYER_NORTH_Y 13
#define PLAYER_EAST_X 15
#define PLAYER_EAST_Y 0

typedef struct {
    u8 lives, animationTime, firing, poweredUp, x, y, dir;
    u8 hookDir, hookX, hookY, hookDX, hookDY, hookEnabled;
    u16 scoreDelta;
    u32 score;
} Player;

extern Player players[];
extern u8 activePlayer;

void PlayerStart(u8);
void PlayerAddScoreDelta(u16);
void PlayerFlushScore();
void PlayerResume();
void PlayerInput();
void PlayerUpdate();

#endif