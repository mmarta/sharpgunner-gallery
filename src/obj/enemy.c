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

void EnemyDeacticvate(u8);
void EnemyInvaderUpdate(u8);
void EnemySweeperUpdate(u8);

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
                    enemyPool[i].score = 100;
                    DrawMap(
                        enemyPool[i].x, enemyPool[i].y,
                        mapInvaderA[enemyPool[i].dir]
                    );
                    break;
                case SWEEPER:
                    enemyPool[i].score = 250;
                    DrawMap(
                        enemyPool[i].x, enemyPool[i].y,
                        mapSweeperA[enemyPool[i].dir]
                    );
                    break;
            }
            return;
        }
    }
}

void EnemyDeactivate(u8 i) {
    Fill(enemyPool[i].x, enemyPool[i].y, ENEMY_WIDTH, ENEMY_HEIGHT, 0);
    enemyPool[i].active = false;
}

void EnemyInvaderUpdate(u8 i) {
    s8 xDelta = 0, yDelta = 0;
    switch(enemyPool[i].dir) {
        case WEST:
            yDelta = 1;
            break;
        case NORTH:
            xDelta = -1;
            break;
        case EAST:
            yDelta = -1;
            break;
        default:
            xDelta = 1;
    }

    enemyPool[i].animationTime = enemyPool[i].animationTime == 79 ? 0 : enemyPool[i].animationTime + 1;

    // Update on next animation
    if(enemyPool[i].animationTime == 0 || enemyPool[i].animationTime == 40) {
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
    } else if(
        enemyPool[i].movements >= 6
        && (enemyPool[i].animationTime == 20 || enemyPool[i].animationTime == 60)
    ) {
        DrawMap(enemyPool[i].x, enemyPool[i].y, mapInvaderWarn[enemyPool[i].dir]);
    }
}

void EnemySweeperUpdate(u8 i) {
    s8 xDelta = 0, yDelta = 0;
    switch(enemyPool[i].dir) {
        case WEST:
            yDelta = 1;
            break;
        case NORTH:
            xDelta = -1;
            break;
        case EAST:
            yDelta = -1;
            break;
        default:
            xDelta = 1;
    }

    enemyPool[i].animationTime = enemyPool[i].animationTime == 7 ? 0 : enemyPool[i].animationTime + 1;

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

    if(!enemyPool[i].animationTime) {
        DrawMap(enemyPool[i].x, enemyPool[i].y, mapSweeperA[enemyPool[i].dir]);
    } else if(enemyPool[i].animationTime == 4) {
        DrawMap(enemyPool[i].x, enemyPool[i].y, mapSweeperB[enemyPool[i].dir]);
    }
}

void EnemyUpdate(u8 i) {
    if(!enemyPool[i].active) {
        return;
    }

    if(enemyPool[i].killTime > 0) {
        if(enemyPool[i].killTime == 17) {
            EnemyDeactivate(i);
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
    }
}

void EnemyKill(u8 i) {
    enemyPool[i].killTime = 1;
}
