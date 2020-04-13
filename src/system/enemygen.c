#include "enemygen.h"

u8 enemyGenSpawnTimeout = 0;
u8 enemyGenLeft = 0;
direction lastSpawnDirection = SOUTH;

void EnemyGenLevelBegin() {
    const Level *currentLevel = &levels[players[activePlayer].level];
    enemyGenLeft = currentLevel->enemyTotal;
    enemyGenSpawnTimeout = currentLevel->minGenTime + (rand() % currentLevel->randomFactor);
    PrintVerticalRAM(30, 10, "MONSTERS");
    PrintU8Vertical(30, 0, enemyGenLeft);
}

void EnemyGenEngineTick() {
    // Nothing to generate? Leave.
    if(!enemyGenLeft) {
        return;
    }

    // Next tick
    else if(enemyGenSpawnTimeout) {
        enemyGenSpawnTimeout--;
        return;
    }

    const Level *currentLevel = &levels[players[activePlayer].level];

    // Pick next enemy from factors
    direction nextDirection = rand() % 4;
    if(nextDirection == lastSpawnDirection) {
        nextDirection = (nextDirection + 1) % 4;
    }
    u8 enemyPickedID = rand() % (currentLevel->invaderFactor + currentLevel->sweeperFactor + currentLevel->sparxFactor);
    if(enemyPickedID < currentLevel->invaderFactor) {
        EnemyInit(nextDirection, INVADER);
    } else if(enemyPickedID < currentLevel->invaderFactor + currentLevel->sweeperFactor) {
        EnemyInit(nextDirection, SWEEPER);
    } else {
        EnemyInit(nextDirection, SPARX);
    }

    // Set next timeout
    enemyGenSpawnTimeout = currentLevel->minGenTime + (rand() % currentLevel->randomFactor);
    enemyGenLeft--;
    PrintU8Vertical(30, 0, enemyGenLeft);
    lastSpawnDirection = nextDirection;
}
