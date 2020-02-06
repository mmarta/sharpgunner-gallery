#include "system/defines.h"
#include "system/graphics.h"
#include "obj/bullet.h"
#include "obj/player.h"

const char str[] PROGMEM = "HELLO";
const char strA[] = "BYE";

int main() {
    u8 i;

    SetTileTable(bgFontTiles);
    ClearVram();

    SetSpritesTileTable(spriteTiles);
    SetSpriteVisibility(1);

    PlayerStart(0);
    activePlayer = 0;
    PlayerResume();

    while(1) {
        WaitVsync(1);

        for(i = 0; i < BULLET_COUNT; i++) {
            BulletUpdate(i);
        }
        PlayerUpdate();
        
        PlayerInput();
    }

    return 0;
}