#include "game.h"

void GameStart(u8 playerCount) {
    PlayerStart(0);
    if(playerCount) {
        PlayerStart(1);
    }
    activePlayer = 0;
    playersInGame = playerCount;

    LevelStart();
    LevelDisplayReady();
    PlayerResume();
    EnemyGenLevelBegin();

    BackgroundStart();
}

void GameUpdate() {
    u8 i;
    
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
    MachineInput();
    PlayerInput();
}
