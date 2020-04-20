#include "system/defines.h"
#include "system/graphics.h"
#include "system/background.h"
#include "obj/laser.h"
#include "obj/player.h"
#include "obj/enemy.h"
#include "obj/collision.h"
#include "system/level.h"
#include "system/enemygen.h"

u32 hi = 10000;

void DrawHiLabel() {
    SetTile(0, 13, 71);
    SetTile(0, 14, 70);
}

int main() {
    u8 i;

    srand(GetTrueRandomSeed());

    SetTileTable(tiles);
    ClearVram();

    DrawHiLabel();
    PrintU32Vertical(1, 11, hi, 9999999);

    BackgroundStart();

    PlayerStart(0);
    PlayerStart(1);
    activePlayer = 0;
    playersInGame = 2;

    LevelStart();
    LevelDisplayReady();
    PlayerResume();
    EnemyGenLevelBegin();

    while(1) {
        WaitVsync(1);

        // BG Stuff first
        PlayerFlushScore();
        if(players[activePlayer].score > hi) {
            hi = players[activePlayer].score;
            PrintU32Vertical(1, 11, hi, 9999999);
        }

        BackgroundUpdate();

        // ...then collisions
        CollisionRunAll();

        // Level enemy gen next
        LevelUpdate();
        EnemyGenEngineTick();

        // Sprite stuff next
        i = LASER_COUNT;
        while(i--) {
            LaserUpdate(i);
        }

        i = ENEMY_COUNT;
        while(i--) {
            EnemyUpdate(i);
        }

        if(!PlayerUpdate()) {
            if(LevelPlayerDeath()) {
                PlayerResume();
            } else {
                // Todo: Remove this.
                Fill(2, 0, 28, 28, 0);
                while(true) {
                    WaitVsync(1);
                }
            }
        }

        // Input
        PlayerInput();
    }

    return 0;
}
