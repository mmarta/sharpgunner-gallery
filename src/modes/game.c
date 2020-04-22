#include "game.h"

void GameStart(u8 playerCount) {
    machineMode = GAME;
    PlayerStart(0);
    if(playerCount == 2) {
        PlayerStart(1);
    }
    activePlayer = 0;
    playersInGame = playerCount;

    Fill(30, 0, 2, 28, 0);

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
            machineMode = TITLE;
            return;
        }
    }

    // Input
    PlayerInput();
}
