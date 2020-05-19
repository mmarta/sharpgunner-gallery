#include "enemygen.h"

u8 enemyGenSpawnTimeout = 0;
direction lastSpawnDirection = SOUTH;

void EnemyGenLevelBegin() {
    u8 levelToGrab = players[activePlayer].level >= 12
        ? (players[activePlayer].level % 3) + 9
        : players[activePlayer].level;
    const Level *currentLevel = &levels[levelToGrab];
    enemyGenSpawnTimeout = currentLevel->minGenTime + (rand() % currentLevel->randomFactor);
}

void EnemyGenEngineTick() {
    // Next tick
    if(enemyGenSpawnTimeout) {
        enemyGenSpawnTimeout--;
        return;
    }

    u8 levelToGrab = players[activePlayer].level >= 12
        ? (players[activePlayer].level % 3) + 9
        : players[activePlayer].level;

    const Level *currentLevel = &levels[levelToGrab];

    // Pick next enemy from factors
    direction nextDirection = rand() % 4;
    if(nextDirection == lastSpawnDirection) {
        nextDirection = (nextDirection + 1) % 4;
    }

    u8 enemyPickedID = rand() % (
        currentLevel->invaderFactor + currentLevel->sweeperFactor + currentLevel->sparxFactor
        + currentLevel->nucleusFactor + currentLevel->asteroidFactor
    );

    if(enemyPickedID < currentLevel->invaderFactor) {
        EnemyInit(nextDirection, INVADER);
    } else if(enemyPickedID < currentLevel->invaderFactor + currentLevel->sweeperFactor) {
        EnemyInit(nextDirection, SWEEPER);
    } else if(enemyPickedID < currentLevel->invaderFactor + currentLevel->sweeperFactor + currentLevel->sparxFactor) {
        EnemyInit(nextDirection, SPARX);
    } else if(
        enemyPickedID < currentLevel->invaderFactor + currentLevel->sweeperFactor
        + currentLevel->sparxFactor + currentLevel->nucleusFactor
    ) {
        EnemyInit(nextDirection, NUCLEUS);
    } else {
        EnemyInit(nextDirection, ASTEROID);
    }

    // Set next timeout
    enemyGenSpawnTimeout = currentLevel->minGenTime + (rand() % currentLevel->randomFactor);
    lastSpawnDirection = nextDirection;
}
