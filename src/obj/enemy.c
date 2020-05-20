#include "enemy.h"

Enemy enemyPool[ENEMY_COUNT];

u8 enemyStartXCoords[] = {
    ENEMY_SOUTH_START_X, ENEMY_WEST_START_X,
    ENEMY_NORTH_START_X, ENEMY_EAST_START_X
};

u8 enemyStartYCoords[] = {
    ENEMY_SOUTH_START_Y, ENEMY_WEST_START_Y,
    ENEMY_NORTH_START_Y, ENEMY_EAST_START_Y
};

void EnemyGetDelta(s8 *, s8 *, direction *);
void EnemyInvaderUpdate(u8);
void EnemySweeperUpdate(u8);
void EnemySparxUpdate(u8);
void EnemyNucleusUpdate(u8);
void EnemyAsteroidUpdate(u8);

void EnemyInit(direction dir, enemytype type) {
    u8 i = ENEMY_COUNT;
    while(i--) {
        if(!enemyPool[i].active) {
            enemyPool[i].dir = dir;
            enemyPool[i].x = enemyStartXCoords[dir];
            enemyPool[i].y = enemyStartYCoords[dir];
            enemyPool[i].type = type;
            enemyPool[i].animationTime = 0;
            enemyPool[i].killTime = 0;
            enemyPool[i].movements = 0;
            enemyPool[i].active = true;

            switch(type) {
                case INVADER:
                    enemyPool[i].score = 200;
                    DrawMap(
                        enemyPool[i].x, enemyPool[i].y,
                        mapInvaderA[enemyPool[i].dir]
                    );
                    break;
                case SWEEPER:
                    enemyPool[i].score = 500;
                    DrawMap(
                        enemyPool[i].x, enemyPool[i].y,
                        mapSweeperA[enemyPool[i].dir]
                    );
                    break;
                case SPARX:
                    enemyPool[i].score = 1000;
                    DrawMap(
                        enemyPool[i].x, enemyPool[i].y,
                        mapSparxA[enemyPool[i].dir]
                    );
                    break;
                case NUCLEUS:
                    enemyPool[i].score = 400;
                    DrawMap(
                        enemyPool[i].x, enemyPool[i].y,
                        mapEnemyNucleusLarge
                    );
                    break;
                case ASTEROID:
                    enemyPool[i].score = 0;
                    DrawMap(
                        enemyPool[i].x, enemyPool[i].y,
                        mapEnemyAsteroid
                    );
                    break;
            }
            return;
        }
    }
}

void EnemyDeactivate(u8 i) {
    if(enemyPool[i].active) {
        Fill(enemyPool[i].x, enemyPool[i].y, ENEMY_WIDTH, ENEMY_HEIGHT, 0);
        enemyPool[i].active = false;
    }
}

void EnemyGetDelta(s8 *dX, s8 *dY, direction *dir) {
    switch(*dir) {
        case WEST:
            *dY = 1;
            break;
        case NORTH:
            *dX = -1;
            break;
        case EAST:
            *dY = -1;
            break;
        default:
            *dX = 1;
    }
}

void EnemyInvaderUpdate(u8 i) {
    s8 xDelta = 0, yDelta = 0;
    EnemyGetDelta(&xDelta, &yDelta, &enemyPool[i].dir);

    u8 flipTime = players[activePlayer].level > 4 ? 29 : 39;

    enemyPool[i].animationTime = enemyPool[i].animationTime == flipTime ? 0 : enemyPool[i].animationTime + 1;

    // Update on next animation
    if(enemyPool[i].animationTime == 0 || enemyPool[i].animationTime == ((flipTime >> 1) + 1)) {
        Fill(enemyPool[i].x, enemyPool[i].y, ENEMY_WIDTH, ENEMY_HEIGHT, 0);
        enemyPool[i].x += xDelta;
        enemyPool[i].y += yDelta;
        enemyPool[i].movements++;

        // Reached the player? Then Deactivate
        if(
            enemyPool[i].x == playerXCoords[enemyPool[i].dir]
            && enemyPool[i].y == playerYCoords[enemyPool[i].dir]
        ) {
            EnemyDeactivate(i);
        } else {
            DrawMap(
                enemyPool[i].x, enemyPool[i].y,
                enemyPool[i].animationTime
                    ? mapInvaderB[enemyPool[i].dir]
                    : mapInvaderA[enemyPool[i].dir]
            );
        }
    }
}

void EnemySweeperUpdate(u8 i) {
    s8 xDelta = 0, yDelta = 0;
    EnemyGetDelta(&xDelta, &yDelta, &enemyPool[i].dir);

    u8 flipTime = players[activePlayer].level > 3 ? 7 : 11;

    enemyPool[i].animationTime = enemyPool[i].animationTime == flipTime ? 0 : enemyPool[i].animationTime + 1;

    // Update on next animation
    if(!enemyPool[i].animationTime) {
        Fill(enemyPool[i].x, enemyPool[i].y, ENEMY_WIDTH, ENEMY_HEIGHT, 0);
        enemyPool[i].x += xDelta;
        enemyPool[i].y += yDelta;
        enemyPool[i].movements++;

        // Reached the player? Then Deactivate
        if(
            enemyPool[i].x == playerXCoords[enemyPool[i].dir]
            && enemyPool[i].y == playerYCoords[enemyPool[i].dir]
        ) {
            EnemyDeactivate(i);
            return;
        }

        DrawMap(enemyPool[i].x, enemyPool[i].y, mapSweeperA[enemyPool[i].dir]);
    } else if(enemyPool[i].animationTime == 4) {
        DrawMap(enemyPool[i].x, enemyPool[i].y, mapSweeperB[enemyPool[i].dir]);
    }
}

void EnemySparxUpdate(u8 i) {
    s8 xDelta = 0, yDelta = 0;
    EnemyGetDelta(&xDelta, &yDelta, &enemyPool[i].dir);

    enemyPool[i].animationTime = enemyPool[i].animationTime == 79 ? 0 : enemyPool[i].animationTime + 1;

    // Update on next animation
    if(!enemyPool[i].animationTime) {
        Fill(enemyPool[i].x, enemyPool[i].y, ENEMY_WIDTH, ENEMY_HEIGHT, 0);
        enemyPool[i].x += xDelta;
        enemyPool[i].y += yDelta;
        enemyPool[i].movements++;

        // Reached the player? Then Deactivate
        if(
            enemyPool[i].x == playerXCoords[enemyPool[i].dir]
            && enemyPool[i].y == playerYCoords[enemyPool[i].dir]
        ) {
            EnemyDeactivate(i);
            return;
        }
    }

    switch(enemyPool[i].animationTime) {
        case 0:
            DrawMap(enemyPool[i].x, enemyPool[i].y, mapSparxA[enemyPool[i].dir]);
            break;
        case 10:
        case 70:
            DrawMap(enemyPool[i].x, enemyPool[i].y, mapSparxB[enemyPool[i].dir]);
            break;
        case 20:
        case 30:
        case 40:
        case 50:
        case 60:
            DrawMap(enemyPool[i].x, enemyPool[i].y, mapSparxC[enemyPool[i].dir]);
            break;
    }
}

void EnemyNucleusUpdate(u8 i) {
    s8 xDelta = 0, yDelta = 0;
    EnemyGetDelta(&xDelta, &yDelta, &enemyPool[i].dir);

    // First phase
    if(enemyPool[i].animationTime < 60) {
        enemyPool[i].animationTime = enemyPool[i].animationTime == 19 ? 0 : enemyPool[i].animationTime + 1;
    } else {
        enemyPool[i].animationTime = enemyPool[i].animationTime == 63 ? 60 : enemyPool[i].animationTime + 1;
    }

    // Update on next animation
    if(!enemyPool[i].animationTime || enemyPool[i].animationTime == 60) {
        Fill(enemyPool[i].x, enemyPool[i].y, ENEMY_WIDTH, ENEMY_HEIGHT, 0);
        enemyPool[i].x += xDelta;
        enemyPool[i].y += yDelta;
        enemyPool[i].movements++;

        // Reached the player? Then Deactivate
        if(
            enemyPool[i].x == playerXCoords[enemyPool[i].dir]
            && enemyPool[i].y == playerYCoords[enemyPool[i].dir]
        ) {
            EnemyDeactivate(i);
            return;
        }
    }

    switch(enemyPool[i].animationTime) {
        case 0:
            DrawMap(enemyPool[i].x, enemyPool[i].y, mapEnemyNucleusLarge);
            break;
        case 60:
            DrawMap(enemyPool[i].x, enemyPool[i].y, mapEnemyNucleusSmall);
            break;
    }
}

void EnemyAsteroidUpdate(u8 i) {
    s8 xDelta = 0, yDelta = 0;
    EnemyGetDelta(&xDelta, &yDelta, &enemyPool[i].dir);

    u8 flipTime = players[activePlayer].level > 5 ? 7 : 11;

    // First phase
    enemyPool[i].animationTime = enemyPool[i].animationTime == flipTime ? 0 : enemyPool[i].animationTime + 1;

    // Update on next animation
    if(!enemyPool[i].animationTime) {
        Fill(enemyPool[i].x, enemyPool[i].y, ENEMY_WIDTH, ENEMY_HEIGHT, 0);
        enemyPool[i].x += xDelta;
        enemyPool[i].y += yDelta;
        enemyPool[i].movements++;

        // Reached the player? Then Deactivate
        if(
            enemyPool[i].x == playerXCoords[enemyPool[i].dir]
            && enemyPool[i].y == playerYCoords[enemyPool[i].dir]
        ) {
            EnemyDeactivate(i);
            return;
        } else {
            DrawMap(enemyPool[i].x, enemyPool[i].y, mapEnemyAsteroid);
        }
    }
}

void EnemyUpdate(u8 i) {
    if(!enemyPool[i].active) {
        return;
    }

    if(enemyPool[i].killTime > 0) {
        if(enemyPool[i].killTime == 17) {
            // Nucleus 1st hit?
            if(enemyPool[i].type == NUCLEUS && enemyPool[i].animationTime < 60) {
                enemyPool[i].killTime = 0;
                enemyPool[i].score = 1200;
                enemyPool[i].animationTime = 60;
                DrawMap(enemyPool[i].x, enemyPool[i].y, mapEnemyNucleusSmall);
            } else { // Destroy anything else
                EnemyDeactivate(i);
            }

            return;
        } else if(enemyPool[i].killTime % 4 == 1) {
            DrawMap(enemyPool[i].x, enemyPool[i].y, mapEnemyKill[enemyPool[i].killTime / 4]);
        }
        enemyPool[i].killTime++;
        return;
    }

    switch(enemyPool[i].type) {
        case INVADER:
            EnemyInvaderUpdate(i);
            break;
        case SWEEPER:
            EnemySweeperUpdate(i);
            break;
        case SPARX:
            EnemySparxUpdate(i);
            break;
        case NUCLEUS:
            EnemyNucleusUpdate(i);
            break;
        case ASTEROID:
            EnemyAsteroidUpdate(i);
            break;
    }
}

void EnemyKill(u8 i, u8 playSound) {
    // Don't "kill" an asteroid
    if(enemyPool[i].type == ASTEROID) {
        DrawMap(enemyPool[i].x, enemyPool[i].y, mapEnemyAsteroid);
        if(playSound) {
            if(attractSound || machineMode == GAME) {
                SFXPlay(PATCH_TINK);
            }
        }
        return;
    }

    if(playSound) {
        if(attractSound || machineMode == GAME) {
            SFXPlay(PATCH_ENEMY_KILL);
        }
    }
    enemyPool[i].killTime = 1;
}
