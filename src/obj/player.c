#include "player.h"

Player players[PLAYER_COUNT];

u8 playerXCoords[] = {
    PLAYER_SOUTH_X, PLAYER_WEST_X,
    PLAYER_NORTH_X, PLAYER_EAST_X
};

u8 playerYCoords[] = {
    PLAYER_SOUTH_Y, PLAYER_WEST_Y,
    PLAYER_NORTH_Y, PLAYER_EAST_Y
};

const char pBlankStr[] PROGMEM = "   ";

u8 activePlayer = 0;
u8 toggleTime = 0;
u8 fireTimeout = 0;

void PlayerDrawScoreLabel(u8);
void PlayerSetDirCoordinates();
void PlayerFire();
void PlayerDrawTiles();
void PlayerMoveHook();

void PlayerStart(u8 i) {
    players[i].lives = 3;
    players[i].score = 0;
    players[i].poweredUp = 0;
    players[i].active = true;
    players[i].level = 0;
    PlayerDrawScoreLabel(i);
    PrintU32Vertical(1, i ? 0 : 21, players[i].score, 9999999);
}

void PlayerSetDirCoordinates() {
    players[activePlayer].x = playerXCoords[players[activePlayer].dir];
    players[activePlayer].y = playerYCoords[players[activePlayer].dir];
}

void PlayerAddScoreDelta(u16 val) {
    players[activePlayer].scoreDelta += val;
}

void PlayerFlushScore() {
    if(players[activePlayer].scoreDelta) {
        players[activePlayer].score += players[activePlayer].scoreDelta;
        players[activePlayer].scoreDelta = 0;
        PrintU32Vertical(1, activePlayer ? 0 : 21, players[activePlayer].score, 9999999);
    }

    toggleTime = toggleTime == 59 ? 0 : toggleTime + 1;
    switch(toggleTime) {
        case 0:
            PlayerDrawScoreLabel(activePlayer);
            break;
        case 30:
            PrintVerticalPROGMEM(0, activePlayer ? 4 : 25, pBlankStr);
    }
}

void PlayerDrawScoreLabel(u8 i) {
    if(i) {
        SetTile(0, 2, 69);
        SetTile(0, 3, 68);
        SetTile(0, 4, 67);
    } else {
        SetTile(0, 23, 66);
        SetTile(0, 24, 65);
        SetTile(0, 25, 64);
    }
}

void PlayerResume() {
    players[activePlayer].animationTime = 0;
    players[activePlayer].killTime = 0;
    players[activePlayer].hookEnabled = false;
    toggleTime = 59;

    // Back to south
    Fill(players[activePlayer].x, players[activePlayer].y, PLAYER_WIDTH, PLAYER_HEIGHT, 0);
    players[activePlayer].dir = SOUTH;
    PlayerSetDirCoordinates();
    DrawMap(players[activePlayer].x, players[activePlayer].y, mapFighterSouthA);
}

void PlayerFire() {
    u8 x, y;
    if(!fireTimeout) {
        switch(players[activePlayer].dir) {
            case WEST:
                x = players[activePlayer].x;
                y = players[activePlayer].y - 1;
                break;
            case NORTH:
                x = players[activePlayer].x + 2;
                y = players[activePlayer].y;
                break;
            case EAST:
                x = players[activePlayer].x;
                y = players[activePlayer].y + 2;
                break;
            default:
                x = players[activePlayer].x - 1;
                y = players[activePlayer].y;
        }

        if(LaserInit(players[activePlayer].dir, x, y)) {
            fireTimeout = 2;
        }
    }
}

void PlayerMoveHook() {
    if(
        players[activePlayer].x == players[activePlayer].hookDX
        && players[activePlayer].y == players[activePlayer].hookDY
    ) { // Finishing
        players[activePlayer].dir = players[activePlayer].hookDir;
        PlayerSetDirCoordinates();
        players[activePlayer].hookEnabled = false;
    } else if(
        players[activePlayer].hookX == players[activePlayer].hookDX
        || players[activePlayer].hookY == players[activePlayer].hookDY
    ) { // Moving the player
        Fill(players[activePlayer].x, players[activePlayer].y, PLAYER_WIDTH, PLAYER_HEIGHT, 0);

        switch(players[activePlayer].hookDir) {
            case WEST:
                players[activePlayer].y++;
                players[activePlayer].x += players[activePlayer].dir == NORTH ? 1 : -1;
                break;
            case EAST:
                players[activePlayer].y--;
                players[activePlayer].x += players[activePlayer].dir == NORTH ? 1 : -1;
                break;
            case NORTH:
                players[activePlayer].x--;
                players[activePlayer].y += players[activePlayer].dir == EAST ? 1 : -1;
                break;
            default:
                players[activePlayer].x++;
                players[activePlayer].y += players[activePlayer].dir == EAST ? 1 : -1;
                break;
        }

        PlayerDrawTiles();
    } else { // Moving the hook
        switch(players[activePlayer].hookDir) {
            case WEST:
                if(players[activePlayer].dir == NORTH) {
                    DrawMap(players[activePlayer].hookX, players[activePlayer].hookY, mapWireA);
                    players[activePlayer].hookY++;
                    players[activePlayer].hookX++;
                    DrawMap(players[activePlayer].hookX, players[activePlayer].hookY, mapHookSW);
                } else {
                    DrawMap(players[activePlayer].hookX, players[activePlayer].hookY, mapWireB);
                    players[activePlayer].hookY++;
                    players[activePlayer].hookX--;
                    DrawMap(players[activePlayer].hookX, players[activePlayer].hookY, mapHookNW);
                }
                break;
            case EAST:
                if(players[activePlayer].dir == NORTH) {
                    DrawMap(players[activePlayer].hookX, players[activePlayer].hookY, mapWireB);
                    players[activePlayer].hookY--;
                    players[activePlayer].hookX++;
                    DrawMap(players[activePlayer].hookX, players[activePlayer].hookY, mapHookSE);
                } else {
                    DrawMap(players[activePlayer].hookX, players[activePlayer].hookY, mapWireA);
                    players[activePlayer].hookY--;
                    players[activePlayer].hookX--;
                    DrawMap(players[activePlayer].hookX, players[activePlayer].hookY, mapHookNE);
                }
                break;
            case NORTH:
                if(players[activePlayer].dir == WEST) {
                    DrawMap(players[activePlayer].hookX, players[activePlayer].hookY, mapWireA);
                    players[activePlayer].hookY--;
                    players[activePlayer].hookX--;
                    DrawMap(players[activePlayer].hookX, players[activePlayer].hookY, mapHookNE);
                } else {
                    DrawMap(players[activePlayer].hookX, players[activePlayer].hookY, mapWireB);
                    players[activePlayer].hookY++;
                    players[activePlayer].hookX--;
                    DrawMap(players[activePlayer].hookX, players[activePlayer].hookY, mapHookNW);
                }
                break;
            default:
                if(players[activePlayer].dir == WEST) {
                    DrawMap(players[activePlayer].hookX, players[activePlayer].hookY, mapWireB);
                    players[activePlayer].hookY--;
                    players[activePlayer].hookX++;
                    DrawMap(players[activePlayer].hookX, players[activePlayer].hookY, mapHookSE);
                } else {
                    DrawMap(players[activePlayer].hookX, players[activePlayer].hookY, mapWireA);
                    players[activePlayer].hookY++;
                    players[activePlayer].hookX++;
                    DrawMap(players[activePlayer].hookX, players[activePlayer].hookY, mapHookSW);
                }
                break;
        }

        if(players[activePlayer].animationTime % 2 == 0) {
            PlayerDrawTiles();
        }
    }
}

void PlayerDrawTiles() {
    if(players[activePlayer].killTime) {
        if(players[activePlayer].killTime % 6 == 1) {
            DrawMap(players[activePlayer].x, players[activePlayer].y, mapFighterKill[players[activePlayer].killTime / 6]);
        }
        return;
    }

    if(players[activePlayer].animationTime < 2) {
        DrawMap(players[activePlayer].x, players[activePlayer].y, mapFighterA[players[activePlayer].dir]);
    } else if(players[activePlayer].animationTime < 4 || players[activePlayer].animationTime >= 6) {
        DrawMap(players[activePlayer].x, players[activePlayer].y, mapFighterB[players[activePlayer].dir]);
    } else {
        DrawMap(players[activePlayer].x, players[activePlayer].y, mapFighterC[players[activePlayer].dir]);
    }
}

void PlayerInput() {
    if(
        !players[activePlayer].active || players[activePlayer].hookEnabled
        || players[activePlayer].killTime
    ) {
        return;
    }

    int stick = ReadJoypad(activePlayer);

    if(stick & BTN_LEFT) {
        if(players[activePlayer].dir == NORTH || players[activePlayer].dir == SOUTH) {
            players[activePlayer].hookDir = WEST;
            players[activePlayer].hookX = players[activePlayer].x + (players[activePlayer].dir == NORTH ? 2 : -1);
            players[activePlayer].hookY = players[activePlayer].y + 2;
            players[activePlayer].hookEnabled = true;
        }
    } else if(stick & BTN_RIGHT) {
        if(players[activePlayer].dir == NORTH || players[activePlayer].dir == SOUTH) {
            players[activePlayer].hookDir = EAST;
            players[activePlayer].hookX = players[activePlayer].x + (players[activePlayer].dir == NORTH ? 2 : -1);
            players[activePlayer].hookY = players[activePlayer].y - 1;
            players[activePlayer].hookEnabled = true;
        }
    } else if(stick & BTN_UP) {
        if(players[activePlayer].dir == EAST || players[activePlayer].dir == WEST) {
            players[activePlayer].hookDir = NORTH;
            players[activePlayer].hookY = players[activePlayer].y + (players[activePlayer].dir == EAST ? 2 : -1);
            players[activePlayer].hookX = players[activePlayer].x - 1;
            players[activePlayer].hookEnabled = true;
        }
    } else if(stick & BTN_DOWN) {
        if(players[activePlayer].dir == EAST || players[activePlayer].dir == WEST) {
            players[activePlayer].hookDir = SOUTH;
            players[activePlayer].hookY = players[activePlayer].y + (players[activePlayer].dir == EAST ? 2 : -1);
            players[activePlayer].hookX = players[activePlayer].x + 2;
            players[activePlayer].hookEnabled = true;
        }
    }

    // Did we grapple off this round?
    if(players[activePlayer].hookEnabled) {
        players[activePlayer].hookDX = playerXCoords[players[activePlayer].hookDir];
        players[activePlayer].hookDY = playerYCoords[players[activePlayer].hookDir];
    }

    if(stick & BTN_A) {
        if(!players[activePlayer].firing) {
            PlayerFire();
            players[activePlayer].firing = 1;
        }
    } else {
        if(players[activePlayer].firing) {
           players[activePlayer].firing = 0;
        }
    }
}

void PlayerUpdate() {
    if(!players[activePlayer].active) {
        return;
    }

    if(fireTimeout) {
        fireTimeout--;
    }

    if(players[activePlayer].killTime) {
        PlayerDrawTiles();
        players[activePlayer].killTime++;
        if(players[activePlayer].killTime == 25) {
            players[activePlayer].killTime = 0;
            players[activePlayer].lives--;
            PlayerResume(); // Move this later
        }
        return;
    }

    players[activePlayer].animationTime =
        players[activePlayer].animationTime == 7
        ? 0
        : players[activePlayer].animationTime + 1;

    if(players[activePlayer].hookEnabled) {
        PlayerMoveHook();
        return;
    }

    if(players[activePlayer].animationTime % 2 == 0) {
        PlayerDrawTiles();
    }
}

void PlayerKill() {
    players[activePlayer].killTime = 1;
}
