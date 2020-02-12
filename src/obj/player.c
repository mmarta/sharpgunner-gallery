#include "player.h"

Player players[PLAYER_COUNT];

const char pBlankStr[] PROGMEM = "   ";

u8 activePlayer = 0;
u8 toggleTime = 0;
u8 fireTimeout = 0;

void PlayerDrawScoreLabel(u8);
void PlayerSetDirCoordinates();

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

void PlayerInput() {
    int stick = ReadJoypad(activePlayer);

    if(stick & BTN_LEFT) {
        Fill(players[activePlayer].x, players[activePlayer].y, PLAYER_WIDTH, PLAYER_HEIGHT, 0);
        players[activePlayer].dir = DIR_WEST;
        PlayerSetDirCoordinates();
        players[activePlayer].animationTime = 7;
    } else if(stick & BTN_RIGHT) {
        Fill(players[activePlayer].x, players[activePlayer].y, PLAYER_WIDTH, PLAYER_HEIGHT, 0);
        players[activePlayer].dir = DIR_EAST;
        PlayerSetDirCoordinates();
        players[activePlayer].animationTime = 7;
    }

    if(stick & BTN_UP) {
        Fill(players[activePlayer].x, players[activePlayer].y, PLAYER_WIDTH, PLAYER_HEIGHT, 0);
        players[activePlayer].dir = DIR_NORTH;
        PlayerSetDirCoordinates();
        players[activePlayer].animationTime = 7;
    } else if(stick & BTN_DOWN) {
        Fill(players[activePlayer].x, players[activePlayer].y, PLAYER_WIDTH, PLAYER_HEIGHT, 0);
        players[activePlayer].dir = DIR_SOUTH;
        PlayerSetDirCoordinates();
        players[activePlayer].animationTime = 7;
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
        players[activePlayer].animationTime == 7 ? 0 : players[activePlayer].animationTime + 1;

    switch(players[activePlayer].animationTime) {
        case 0:
            DrawMap(players[activePlayer].x, players[activePlayer].y, mapFighterA[players[activePlayer].dir]);
            break;
        case 2:
        case 6:
            DrawMap(players[activePlayer].x, players[activePlayer].y, mapFighterB[players[activePlayer].dir]);
            break;
        case 4:
            DrawMap(players[activePlayer].x, players[activePlayer].y, mapFighterC[players[activePlayer].dir]);
    }
}