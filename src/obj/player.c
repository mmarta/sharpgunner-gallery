#include "player.h"

Player players[PLAYER_COUNT];

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
    PlayerDrawScoreLabel(i);
    PrintU32Vertical(1, i ? 0 : 21, players[i].score, 9999999);
}

void PlayerSetDirCoordinates() {
    switch(players[activePlayer].dir) {
        case DIR_WEST:
            players[activePlayer].x = PLAYER_WEST_X;
            players[activePlayer].y = PLAYER_WEST_Y;
            break;
        case DIR_NORTH:
            players[activePlayer].x = PLAYER_NORTH_X;
            players[activePlayer].y = PLAYER_NORTH_Y;
            break;
        case DIR_EAST:
            players[activePlayer].x = PLAYER_EAST_X;
            players[activePlayer].y = PLAYER_EAST_Y;
            break;
        default:
            players[activePlayer].x = PLAYER_SOUTH_X;
            players[activePlayer].y = PLAYER_SOUTH_Y;
    }
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
    players[activePlayer].dir = DIR_SOUTH;
    players[activePlayer].animationTime = 0;
    PlayerSetDirCoordinates();
    DrawMap(players[activePlayer].x, players[activePlayer].y, mapFighterSouthA);
}

void PlayerFire() {
    u8 x, y;
    if(!fireTimeout) {
        switch(players[activePlayer].dir) {
            case DIR_WEST:
                x = players[activePlayer].x;
                y = players[activePlayer].y - 1;
                break;
            case DIR_NORTH:
                x = players[activePlayer].x + 2;
                y = players[activePlayer].y;
                break;
            case DIR_EAST:
                x = players[activePlayer].x;
                y = players[activePlayer].y + 2;
                break;
            default:
                x = players[activePlayer].x - 1;
                y = players[activePlayer].y;
        }

        if(LaserInit(players[activePlayer].dir, x, y)) {
            PlayerAddScoreDelta(100);
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
            case DIR_WEST:
                players[activePlayer].y++;
                players[activePlayer].x += players[activePlayer].dir == DIR_NORTH ? 1 : -1;
                break;
            case DIR_EAST:
                players[activePlayer].y--;
                players[activePlayer].x += players[activePlayer].dir == DIR_NORTH ? 1 : -1;
                break;
            case DIR_NORTH:
                players[activePlayer].x--;
                players[activePlayer].y += players[activePlayer].dir == DIR_EAST ? 1 : -1;
                break;
            default:
                players[activePlayer].x++;
                players[activePlayer].y += players[activePlayer].dir == DIR_EAST ? 1 : -1;
                break;
        }

        PlayerDrawTiles();
    } else { // Moving the hook
        switch(players[activePlayer].hookDir) {
            case DIR_WEST:
                if(players[activePlayer].dir == DIR_NORTH) {
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
            case DIR_EAST:
                if(players[activePlayer].dir == DIR_NORTH) {
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
            case DIR_NORTH:
                if(players[activePlayer].dir == DIR_WEST) {
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
                if(players[activePlayer].dir == DIR_WEST) {
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
    if(players[activePlayer].animationTime < 2) {
        DrawMap(players[activePlayer].x, players[activePlayer].y, mapFighterA[players[activePlayer].dir]);
    } else if(players[activePlayer].animationTime < 4 || players[activePlayer].animationTime >= 6) {
        DrawMap(players[activePlayer].x, players[activePlayer].y, mapFighterB[players[activePlayer].dir]);
    } else {
        DrawMap(players[activePlayer].x, players[activePlayer].y, mapFighterC[players[activePlayer].dir]);
    }
}

void PlayerInput() {
    if(players[activePlayer].hookEnabled) {
        return;
    }

    int stick = ReadJoypad(activePlayer);

    if(stick & BTN_LEFT) {
        if(players[activePlayer].dir == DIR_NORTH || players[activePlayer].dir == DIR_SOUTH) {
            players[activePlayer].hookDX = PLAYER_WEST_X;
            players[activePlayer].hookDY = PLAYER_WEST_Y;
            players[activePlayer].hookX = players[activePlayer].x + (players[activePlayer].dir == DIR_NORTH ? 2 : -1);
            players[activePlayer].hookY = players[activePlayer].y + 2;
            players[activePlayer].hookDir = DIR_WEST;
            players[activePlayer].hookEnabled = true;
        }
    } else if(stick & BTN_RIGHT) {
        if(players[activePlayer].dir == DIR_NORTH || players[activePlayer].dir == DIR_SOUTH) {
            players[activePlayer].hookDX = PLAYER_EAST_X;
            players[activePlayer].hookDY = PLAYER_EAST_Y;
            players[activePlayer].hookX = players[activePlayer].x + (players[activePlayer].dir == DIR_NORTH ? 2 : -1);
            players[activePlayer].hookY = players[activePlayer].y - 1;
            players[activePlayer].hookDir = DIR_EAST;
            players[activePlayer].hookEnabled = true;
        }
    } else if(stick & BTN_UP) {
        if(players[activePlayer].dir == DIR_EAST || players[activePlayer].dir == DIR_WEST) {
            players[activePlayer].hookDX = PLAYER_NORTH_X;
            players[activePlayer].hookDY = PLAYER_NORTH_Y;
            players[activePlayer].hookY = players[activePlayer].y + (players[activePlayer].dir == DIR_EAST ? 2 : -1);
            players[activePlayer].hookX = players[activePlayer].x - 1;
            players[activePlayer].hookDir = DIR_NORTH;
            players[activePlayer].hookEnabled = true;
        }
    } else if(stick & BTN_DOWN) {
        if(players[activePlayer].dir == DIR_EAST || players[activePlayer].dir == DIR_WEST) {
            players[activePlayer].hookDX = PLAYER_SOUTH_X;
            players[activePlayer].hookDY = PLAYER_SOUTH_Y;
            players[activePlayer].hookY = players[activePlayer].y + (players[activePlayer].dir == DIR_EAST ? 2 : -1);
            players[activePlayer].hookX = players[activePlayer].x + 2;
            players[activePlayer].hookDir = DIR_SOUTH;
            players[activePlayer].hookEnabled = true;
        }
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
    if(fireTimeout) {
        fireTimeout--;
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