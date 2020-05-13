#include "game.h"

void GameStart(u8 playerCount) {
    u8 i;
    machineMode = GAME;

    Fill(30, 0, 2, 28, 0);

    PlayerStart(0, livesPerPlay);
    if(playerCount == 2) {
        PlayerStart(1, livesPerPlay);
    }
    activePlayer = 0;
    playersInGame = playerCount;

    i = ENEMY_COUNT;
    while(i--) {
        EnemyDeactivate(i);
    }

    i = LASER_COUNT;
    while(i--) {
        LaserDeactivate(i);
    }

    LevelStart();
    MusicPlayPatch(MUSIC_START);
    LevelDisplayReady(170);
    PlayerTurnReset();
    EnemyGenLevelBegin();

    BackgroundStart();
}

void GameUpdate() {
    u8 i;

    // Flush score (if not DEMO)
    if(machineMode == GAME) {
        PlayerFlushScore();
        if(players[activePlayer].score > hi && hi < 9999999) {
            hi = players[activePlayer].score < 9999999 ? players[activePlayer].score : 9999999;
            PrintU32Vertical(1, 11, hi, 9999999);
        }
    }

    // BG Stuff
    BackgroundUpdate();

    // ...then collisions
    CollisionRunAll();

    // Level enemy gen next (if not DEMO)
    if(machineMode == GAME) {
        LevelUpdate();
        EnemyGenEngineTick();
    }

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
            PlayerTurnReset();
        } else {
            // Todo: Remove this.
            machineMode = TITLE;
            return;
        }
    }

    // Input (if not DEMO)
    if(machineMode == GAME) {
        PlayerInput();
    }
}
