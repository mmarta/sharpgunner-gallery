#include "player.h"

Player players[PLAYER_COUNT];

const char p1UPStr[] PROGMEM = "1UP";
const char p2UPStr[] PROGMEM = "2UP";
const char pBlankStr[] PROGMEM = "   ";

u8 activePlayer = 0;

void PlayerStart(u8 i) {
    players[i].lives = 3;
    players[i].score = 0;
    PrintVerticalPROGMEM(0, i ? 4 : 25, i ? p2UPStr : p1UPStr);
}

void PlayerResume() {
    players[activePlayer].animationTime = 0;
    MapSprite(PLAYER_SHIP_SPRITE_ID, spriteMapSharpgunnerA);
    MapSprite(PLAYER_XHAIR_SPRITE_ID, spriteMapCrosshair);
    MoveSprite(PLAYER_SHIP_SPRITE_ID, 224, 104, PLAYER_SHIP_W, PLAYER_SHIP_H);
    MoveSprite(PLAYER_XHAIR_SPRITE_ID, 120, 104, PLAYER_XHAIR_W, PLAYER_XHAIR_H);
}

void PlayerFire() {
    BulletInit(
        players[activePlayer].poweredUp,
        &sprites[PLAYER_SHIP_SPRITE_ID].x, &sprites[PLAYER_SHIP_SPRITE_ID].y,
        sprites[PLAYER_XHAIR_SPRITE_ID].x
    );
}

void PlayerInput() {
    int stick = ReadJoypad(activePlayer);

    if(stick & BTN_LEFT) {
        if(sprites[PLAYER_SHIP_SPRITE_ID].y < 208) {
            MoveSprite(
                PLAYER_SHIP_SPRITE_ID, sprites[PLAYER_SHIP_SPRITE_ID].x,
                sprites[PLAYER_SHIP_SPRITE_ID].y + 2, PLAYER_SHIP_W, PLAYER_SHIP_H
            );
            MoveSprite(
                PLAYER_XHAIR_SPRITE_ID, sprites[PLAYER_XHAIR_SPRITE_ID].x,
                sprites[PLAYER_XHAIR_SPRITE_ID].y + 2, PLAYER_XHAIR_W, PLAYER_XHAIR_H
            );
        }
    } else if(stick & BTN_RIGHT) {
        if(sprites[PLAYER_SHIP_SPRITE_ID].y > 0) {
            MoveSprite(
                PLAYER_SHIP_SPRITE_ID, sprites[PLAYER_SHIP_SPRITE_ID].x,
                sprites[PLAYER_SHIP_SPRITE_ID].y - 2, PLAYER_SHIP_W, PLAYER_SHIP_H
            );
            MoveSprite(
                PLAYER_XHAIR_SPRITE_ID, sprites[PLAYER_XHAIR_SPRITE_ID].x,
                sprites[PLAYER_XHAIR_SPRITE_ID].y - 2, PLAYER_XHAIR_W, PLAYER_XHAIR_H
            );
        }
    }

    if(stick & BTN_UP) {
        if(sprites[PLAYER_XHAIR_SPRITE_ID].x > 16) {
            MoveSprite(
                PLAYER_XHAIR_SPRITE_ID, sprites[PLAYER_XHAIR_SPRITE_ID].x - 2,
                sprites[PLAYER_XHAIR_SPRITE_ID].y, PLAYER_XHAIR_W, PLAYER_XHAIR_H
            );
        }
    } else if(stick & BTN_DOWN) {
        if(sprites[PLAYER_XHAIR_SPRITE_ID].x < 208) {
            MoveSprite(
                PLAYER_XHAIR_SPRITE_ID, sprites[PLAYER_XHAIR_SPRITE_ID].x + 2,
                sprites[PLAYER_XHAIR_SPRITE_ID].y, PLAYER_XHAIR_W, PLAYER_XHAIR_H
            );
        }
    }

    if(stick & BTN_A) {
        if(!players[activePlayer].firing) {
            PlayerFire();
            players[activePlayer].firing = 1;
        }
    } else {
        if(players[activePlayer].firing) {
            players[activePlayer].firing = 0;
        }
    }
}

void PlayerUpdate() {
    players[activePlayer].animationTime =
        players[activePlayer].animationTime == 7 ? 0 : players[activePlayer].animationTime + 1;

    switch(players[activePlayer].animationTime) {
        case 0:
            MapSprite(PLAYER_SHIP_SPRITE_ID, spriteMapSharpgunnerA);
            break;
        case 2:
        case 6:
            MapSprite(PLAYER_SHIP_SPRITE_ID, spriteMapSharpgunnerB);
            break;
        case 4:
            MapSprite(PLAYER_SHIP_SPRITE_ID, spriteMapSharpgunnerC);
    }
}