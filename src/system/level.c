#include "level.h"

const char readyStr[] PROGMEM = "READY!";
const char gameOverStr[] PROGMEM = "GAME  OVER";
const char player1Str[] PROGMEM = "PLAYER 1";
const char player2Str[] PROGMEM = "PLAYER 2";

const Level levels[] = {
    {
        .invaderFactor = 10, .sweeperFactor = 0, .sparxFactor = 0, .nucleusFactor = 0,
        .asteroidFactor = 0, .bonus = 1000, .randomFactor = 140, .minGenTime = 30
    },
    {
        .invaderFactor = 6, .sweeperFactor = 4, .sparxFactor = 0, .nucleusFactor = 0,
        .asteroidFactor = 2, .bonus = 2000, .randomFactor = 130, .minGenTime = 30
    },
    {
        .invaderFactor = 3, .sweeperFactor = 7, .sparxFactor = 0, .nucleusFactor = 0,
        .asteroidFactor = 3, .bonus = 3000, .randomFactor = 110, .minGenTime = 30
    },
    {
        .invaderFactor = 2, .sweeperFactor = 7, .sparxFactor = 2, .nucleusFactor = 0,
        .asteroidFactor = 5, .bonus = 3000, .randomFactor = 100, .minGenTime = 30
    }
};

u8 levelTime = 30;
u8 levelTick = 60;

u8 bonusTextTime = 0;
u16 bonusTextNum = 0;

void LevelIncrease();
void LevelDisplayGameOver();

void LevelStart() {
    levelTime = 30;
    PrintVerticalRAM(30, 6, "TIME");
    PrintU8Vertical(30, 0, levelTime);
    PrintU8Vertical(30, 20, players[activePlayer].level + 1);
    PrintVerticalRAM(30, 27, "STAGE");
}

void LevelIncrease() {
    u8 i = ENEMY_COUNT;
    while(i--) {
        if(enemyPool[i].active && !enemyPool[i].killTime) {
            if(enemyPool[i].type == NUCLEUS) {
                enemyPool[i].animationTime = 60;
            }
            EnemyKill(i);
            PlayerAddScoreDelta(enemyPool[i].score);
        }
    }
    PlayerAddScoreDelta(levels[players[activePlayer].level].bonus);
    bonusTextNum = levels[players[activePlayer].level].bonus;
    players[activePlayer].level++;
    bonusTextTime = 160;
    LevelStart();
}

void LevelUpdate() {
    if(!levelTick) {
        levelTime--;
        PrintU8Vertical(30, 0, levelTime);
        if(!levelTime) {
            LevelIncrease();
        }
        levelTick = 60;
    } else {
        levelTick--;
    }

    if(!bonusTextTime) {
        PrintVerticalRAM(31, 19, "            ");
    } else {
        u8 modTime = bonusTextTime % 32;
        if(modTime == 0) {
            PrintVerticalRAM(31, 19, "BONUS");
            PrintU32Vertical(31, 8, bonusTextNum, 99999);
        } else if(modTime == 16) {
            PrintVerticalRAM(31, 19, "            ");
        }
        bonusTextTime--;
    }
}

u8 LevelPlayerDeath() {
    u8 i, nextPlayer;

    if(!players[activePlayer].active) {
        LevelDisplayGameOver();
    }

    // Move to next player?
    nextPlayer = activePlayer + 1;
    nextPlayer = nextPlayer % playersInGame;
    if(players[nextPlayer].active) {
        activePlayer = nextPlayer;
    }

    // No more players? End here
    if(!players[activePlayer].active) {
        return false;
    }

    // Clear the screen and write
    LevelStart();
    LevelDisplayReady();

    // Deactivate all enemies
    i = ENEMY_COUNT;
    while(i--) {
        EnemyDeactivate(i);
    }

    return true;
}

void LevelDisplayReady() {
    u8 timer = 90;
    Fill(2, 0, 28, 28, 0);
    PrintVerticalPROGMEM(14, 16, readyStr);
    PrintVerticalPROGMEM(16, 17, activePlayer ? player2Str : player1Str);
    while(timer--) {
        MachineInput();
        WaitVsync(1);
    }

    Fill(2, 0, 28, 28, 0);
}

void LevelDisplayGameOver() {
    u8 timer = 180;
    Fill(2, 0, 28, 28, 0);
    PrintVerticalPROGMEM(14, 18, gameOverStr);
    PrintVerticalPROGMEM(16, 17, activePlayer ? player2Str : player1Str);
    while(timer--) {
        MachineInput();
        WaitVsync(1);
    }
    Fill(2, 0, 28, 28, 0);
}
