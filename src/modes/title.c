#include "title.h"

u16 titleTime = 0;
u8 prevCredits = 0;

u8 wireX;
u8 wireY;

void TitleBeginDemo();
void TitleDemoUpdate();
void TitleDemoClean();

void TitleStart() {
    PrintVerticalRAM(31, 18, "CREDITS");
    PrintU8Vertical(31, 9, credits);
    titleTime = 0;
    activePlayer = 0;
}

void TitleBeginDemo() {
    CLEAR_TITLE();
    BackgroundStart();
    PlayerStart(0);
    PlayerResume();

    PrintVerticalRAM(4, 25, "GAME");
    PrintVerticalRAM(4, 5, "OVER");
}

void TitleDemoClean() {
    u8 i;
    players[activePlayer].active = false;

    i = ENEMY_COUNT;
    while(i--) {
        EnemyDeactivate(i);
    }

    i = LASER_COUNT;
    while(i--) {
        LaserDeactivate(i);
    }
}

void TitleUpdate() {
    u8 modTime = titleTime % 60;
    u8 modTimeStarfighter = titleTime % 2;

    // Standard Title Screen
    if(titleTime < 540) {
        // Text sequence
        switch(titleTime) {
            case 0:
                // Clear space & scores aside from Hi
                CLEAR_TITLE();
                Fill(0, 21, 2, 7, 0);
                Fill(0, 0, 2, 7, 0);
                break;
            case 60:
                PrintVerticalRAM(4, 15, "PLAY");
                break;
            case 120:
                PrintVerticalRAM(6, 22, "SHARPGUNNER GALLERY");
                break;
            case 180:
                PrintVerticalRAM(25, 21, "@2020 RED BALLTOP");
                break;
            case 240:
                players[activePlayer].x = 19;
                players[activePlayer].y = 13;
                players[activePlayer].dir = SOUTH;
                break;
            case 248:
                players[activePlayer].dir = WEST;
                break;
            case 256:
                players[activePlayer].dir = NORTH;
                break;
            case 264:
                players[activePlayer].dir = EAST;
                break;
            case 272:
                players[activePlayer].dir = SOUTH;
                break;
            case 300:
                wireX = players[activePlayer].x - 1;
                wireY = players[activePlayer].y + 2;
                DrawMap(wireX, wireY, mapHookNW);
            case 301:
            case 302:
            case 303:
            case 304:
            case 305:
                DrawMap(wireX, wireY, mapWireB);
                wireX--;
                wireY++;
                DrawMap(wireX, wireY, mapHookNW);
                break;
            case 329:
                while(wireX < players[activePlayer].x) {
                    SetTile(wireX, wireY, 0);
                    wireX++;
                    wireY--;
                }
            case 330:
                wireX = players[activePlayer].x - 1;
                wireY = players[activePlayer].y - 1;
                DrawMap(wireX, wireY, mapHookNE);
            case 331:
            case 332:
            case 333:
            case 334:
            case 335:
                DrawMap(wireX, wireY, mapWireA);
                wireX--;
                wireY--;
                DrawMap(wireX, wireY, mapHookNE);
                break;
            case 359:
                while(wireX < players[activePlayer].x) {
                    SetTile(wireX, wireY, 0);
                    wireX++;
                    wireY++;
                }
        }

        // Sharpgunner Starfighter sprite
        if(titleTime >= 240) {
            if(!modTimeStarfighter) {
                PlayerDrawTiles();
            }
        }

        players[activePlayer].animationTime = players[activePlayer].animationTime == 7 ? 0 : players[activePlayer].animationTime + 1;
    } else if(titleTime == 540) { // Begin demo mode
        TitleBeginDemo();
    } else {
        TitleDemoUpdate();
    }

    // Insert coin? Push 1P/2P start?
    if(!modTime || (modTime < 30 && prevCredits != credits)) {
        if(!credits) {
            PrintVerticalRAM(30, 19, "INSERT  COIN");
        } else if(credits == 1) {
            PrintVerticalRAM(30, 20, "PRESS 1P START");
        } else {
            PrintVerticalRAM(30, 23, "PRESS 1P OR 2P START");
        }
    } else if(modTime == 30) {
        Fill(30, 0, 1, 28, 0);
    }

    prevCredits = credits;
    MachineInput();

    // Start
    if(credits) {
        if(inputs[0] & BTN_START) {
            credits--;
            GameStart(1);
            return;
        } else if(inputs[0] & BTN_SELECT) {
            credits -= 2;
            GameStart(2);
            return;
        }
    }


    titleTime++;
    if(titleTime == 900) {
        TitleDemoClean();
        titleTime = 0;
    }
}

void TitleDemoUpdate() {
    if(titleTime == 600) {
        EnemyInit(WEST, INVADER);
    } if(titleTime == 620) {
        PlayerLaunchHook(WEST);
    } if(titleTime == 660) {
        PlayerFire();
    }

    GameUpdate();
}
