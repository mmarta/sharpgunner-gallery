#include "player.h"

Player players[PLAYER_COUNT];

const char pBlankStr[] PROGMEM = "   ";

u8 activePlayer = 0;
u8 toggleTime = 0;

void PlayerDrawScoreLabel(u8);

void PlayerStart(u8 i) {
    players[i].lives = 3;
    players[i].score = 0;
    players[i].poweredUp = 0;
    PlayerDrawScoreLabel(i);
    PrintU32Vertical(1, i ? 0 : 21, players[i].score, 9999999);
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
    DrawMap(28, 13, mapFighterSouthA);
}

void PlayerFire() {
    LaserInit(players[activePlayer].dir);
    PlayerAddScoreDelta(100);
}

void PlayerInput() {
    int stick = ReadJoypad(activePlayer);

    if(stick & BTN_LEFT) {
        
    } else if(stick & BTN_RIGHT) {
        
    }

    if(stick & BTN_UP) {
        
    } else if(stick & BTN_DOWN) {
        
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
    players[activePlayer].animationTime =
        players[activePlayer].animationTime == 7 ? 0 : players[activePlayer].animationTime + 1;

    switch(players[activePlayer].animationTime) {
        case 0:
            DrawMap(28, 13, mapFighterSouthA);
            break;
        case 2:
        case 6:
            DrawMap(28, 13, mapFighterSouthB);
            break;
        case 4:
            DrawMap(28, 13, mapFighterSouthC);
    }
}