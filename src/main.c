#include "system/defines.h"
#include "system/graphics.h"
#include "obj/bullet.h"
#include "obj/player.h"

u32 hi = 10000;

void DrawHiLabel() {
    SetTile(0, 13, 71);
    SetTile(0, 14, 70);
}

int main() {
    u8 i;

    SetTileTable(bgFontTiles);
    ClearVram();

    SetSpritesTileTable(spriteTiles);
    SetSpriteVisibility(1);

    DrawHiLabel();
    PrintU32Vertical(1, 11, hi, 9999999);

    PlayerStart(0);
    PlayerStart(1);
    activePlayer = 0;
    PlayerResume();

    while(1) {
        WaitVsync(1);

        // BG Stuff first
        PlayerFlushScore();
        if(players[activePlayer].score > hi) {
            hi = players[activePlayer].score;
            PrintU32Vertical(1, 11, hi, 9999999);
        }

        // Sprite stuff next
        for(i = 0; i < BULLET_COUNT; i++) {
            if(BulletUpdate(i)) {
                PlayerAddScoreDelta(100);
            }
        }
        PlayerUpdate();
        
        PlayerInput();
    }

    return 0;
}