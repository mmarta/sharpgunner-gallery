#ifndef _PLAYER_H
#define _PLAYER_H

#include "../system/defines.h"
#include "../system/graphics.h"
#include "../audio/audio.h"
#include "../system/machine.h"
#include "laser.h"

#define PLAYER_COUNT 2
#define PLAYER_WIDTH 2
#define PLAYER_HEIGHT 2

#define PLAYER_SOUTH_X EDGE_SOUTH
#define PLAYER_SOUTH_Y 13
#define PLAYER_WEST_X 15
#define PLAYER_WEST_Y EDGE_WEST
#define PLAYER_NORTH_X EDGE_NORTH
#define PLAYER_NORTH_Y 13
#define PLAYER_EAST_X 15
#define PLAYER_EAST_Y EDGE_EAST

typedef struct {
    u8 lives, animationTime, killTime, soundTime, firing, poweredUp, x, y;
    u8 hookX, hookY, hookDX, hookDY, hookEnabled, active, level;
    u16 scoreDelta;
    u32 score, extendScore;
    direction dir, hookDir;
    stickpos stickPosition;
} Player;

extern Player players[];
extern u8 playerXCoords[];
extern u8 playerYCoords[];
extern u8 activePlayer;
extern u8 playersInGame;

void PlayerStart(u8, u8);
void PlayerAddScoreDelta(u16);
void PlayerFlushScore();
void PlayerFire();
void PlayerLaunchHook(direction);
void PlayerTurnReset();
void PlayerInput();
void PlayerDrawTiles();
void PlayerDrawLives(u8);
u8 PlayerUpdate();
void PlayerKill();

#endif
