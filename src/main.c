#include "system/defines.h"
#include "system/graphics.h"
#include "obj/laser.h"
#include "obj/player.h"
#include "obj/enemy.h"
#include "obj/collision.h"

u32 hi = 10000;

void DrawHiLabel() {
    SetTile(0, 13, 71);
    SetTile(0, 14, 70);
}

int main() {
    u8 i;

    SetTileTable(tiles);
    ClearVram();

    DrawHiLabel();
    PrintU32Vertical(1, 11, hi, 9999999);

    PlayerStart(0);
    PlayerStart(1);
    activePlayer = 0;
    PlayerResume();

    EnemyInit(WEST, INVADER);
    EnemyInit(SOUTH, SWEEPER);

    while(1) {
        WaitVsync(1);

        // BG Stuff first
        PlayerFlushScore();
        if(players[activePlayer].score > hi) {
            hi = players[activePlayer].score;
            PrintU32Vertical(1, 11, hi, 9999999);
        }

        // ...then collisions
        CollisionRunAll();

        // Sprite stuff next
        i = LASER_COUNT;
        while(i--) {
            LaserUpdate(i);
        }

        i = ENEMY_COUNT;
        while(i--) {
            EnemyUpdate(i);
        }

        PlayerUpdate();

        PlayerInput();
    }

    return 0;
}
