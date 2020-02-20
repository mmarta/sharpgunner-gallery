#include "collision.h"

u8 CollisionCheck(u8 *, u8 *, u8, u8, u8 *, u8 *, u8, u8);
u8 CollisionEnemyLaserPreCheck(Enemy *, Laser *);

u8 CollisionCheck(
    u8 *x1, u8 *y1, u8 w1, u8 h1,
    u8 *x2, u8 *y2, u8 w2, u8 h2
) {
    if(
        *x1 < w2 + *x2 && *x2 < w1 + *x1
        && *y1 < h2 + *y2 && *y2 < h1 + *y1
    ) {
        return true;
    }

    return false;
}

u8 CollisionEnemyLaserPreCheck(Enemy *enemy, Laser *laser) {
    if(!(*enemy).active || !(*laser).active) {
        return false;
    }

    if((*enemy).killTime > 0) {
        return false;
    }

    return true;
}

void CollisionRunAll() {
    u8 i, j;

    i = ENEMY_COUNT;
    while(i--) {
        j = LASER_COUNT;
        while(j--) {
            if(CollisionEnemyLaserPreCheck(&enemyPool[i], &lasers[j]) && CollisionCheck(
                &enemyPool[i].x, &enemyPool[i].y, ENEMY_WIDTH, ENEMY_HEIGHT,
                &lasers[j].x, &lasers[j].y, lasers[j].w, lasers[j].h
            )) {
                LaserDeactivate(j);
                EnemyKill(i);
                PlayerAddScoreDelta(enemyPool[i].score);
            }
        }
    }
}