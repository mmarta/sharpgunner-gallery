#include "level.h"

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
    }
};

u8 levelTime = 30;
u8 levelTick = 60;

u8 bonusTextTime = 0;
u16 bonusTextNum = 0;

void LevelIncrease();

void LevelStart() {
    levelTime = 30;
    PrintU8Vertical(30, 0, levelTime);
}

void LevelIncrease() {
    u8 i = ENEMY_COUNT;
    u16 scoreTotals;
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
    bonusTextTime = 96;
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
