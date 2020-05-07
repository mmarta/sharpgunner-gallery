#include "test.h"

TestOption selectedOption;
u8 buttonPressed = false;
u8 dirPressed = false;

void TestChangeOption();
void TestShowOption();

void TestInit() {
    machineMode = TEST;

    ClearVram();

    PrintVerticalRAM(2, 22, "SHARPGUNNER GALLERY");
    PrintVerticalRAM(3, 18, "TEST  MENU");

    PrintVerticalRAM(5, 24, "COINS PER PLAY");
    PrintVerticalRAM(6, 24, "DUAL CONTROLS");
    PrintVerticalRAM(7, 24, "ATTRACT SOUND");
    PrintVerticalRAM(8, 24, "SAVE AND EXIT");

    selectedOption = OPTION_COINS;
    while(selectedOption <= OPTION_EXIT) {
        TestShowOption();
        selectedOption++;
    }
    selectedOption = OPTION_COINS;
    PrintVerticalRAM(selectedOption + 5, 26, ">");
}

void TestChangeOption() {
    switch(selectedOption) {
        case OPTION_COINS:
            coinsPerPlay++;
            if(coinsPerPlay == 5) {
                coinsPerPlay = 0;
            }
            break;
        case OPTION_CONTROLS:
            controllers = controllers == 2 ? 1 : 2;
            break;
        case OPTION_ATTRACT_SOUND:
            attractSound = !attractSound;
            break;
        default:
            machineMode = TITLE;
    }

    if(selectedOption != OPTION_EXIT) {
        TestShowOption();
    }
}

void TestShowOption() {
    switch(selectedOption) {
        case OPTION_COINS:
            if(!coinsPerPlay) {
                PrintVerticalRAM(5, 9, "FREE PLAY");
            } else {
                Fill(5, 1, 1, 9, 0);
                PrintU8Vertical(5, 1, coinsPerPlay);
            }
            break;
        case OPTION_CONTROLS:
            if(controllers == 2) {
                PrintVerticalRAM(6, 6, "  DUAL");
            } else {
                PrintVerticalRAM(6, 6, "SINGLE");
            }
            break;
        case OPTION_ATTRACT_SOUND:
            if(attractSound) {
                PrintVerticalRAM(7, 3, " ON");
            } else {
                PrintVerticalRAM(7, 3, "OFF");
            }
            break;
        default:
            return;
    }
}

void TestUpdate() {
    // Change option / Show button pressed
    if(inputs[0] & BTN_A) {
        if(!buttonPressed) {
            TestChangeOption();
            buttonPressed = true;
        }
    } else if(buttonPressed) {
        buttonPressed = false;
    }

    // Next option / Show direction pressed
    if(inputs[0] & BTN_DOWN) {
        if(!dirPressed) {
            SetTile(selectedOption + 5, 26, 0);
            selectedOption++;
            if(selectedOption > OPTION_EXIT) {
                selectedOption = 0;
            }
            PrintVerticalRAM(selectedOption + 5, 26, ">");
            dirPressed = true;
        }
    } else if(inputs[0] & BTN_UP) {
        if(!dirPressed) {
            SetTile(selectedOption + 5, 26, 0);
            selectedOption--;
            if(selectedOption > OPTION_EXIT) {
                selectedOption = OPTION_EXIT;
            }
            PrintVerticalRAM(selectedOption + 5, 26, ">");
            dirPressed = true;
        }
    } else if(dirPressed) {
        dirPressed = false;
    }
}
