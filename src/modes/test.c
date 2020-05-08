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
    PrintVerticalRAM(6, 24, "PANEL CONTROLS");
    PrintVerticalRAM(7, 24, "ATTRACT SOUND");
    PrintVerticalRAM(8, 24, "LIVES PER PLAY");
    PrintVerticalRAM(9, 24, "SAVE AND EXIT");

    PrintVerticalRAM(11, 23, "USE P1 STICK TO MOVE");
    PrintVerticalRAM(12, 24, "USE P1 START TO UPDATE");

    PrintVerticalRAM(15, 18, "INPUT TEST");
    PrintVerticalRAM(17, 18, "P1      P2");
    PrintVerticalRAM(18, 26, "LEFT");
    PrintVerticalRAM(19, 26, "UP");
    PrintVerticalRAM(20, 26, "RIGHT");
    PrintVerticalRAM(21, 26, "DOWN");
    PrintVerticalRAM(22, 26, "FIRE");
    PrintVerticalRAM(23, 26, "COIN");
    PrintVerticalRAM(24, 26, "START");

    selectedOption = OPTION_COINS;
    while(selectedOption <= OPTION_EXIT) {
        TestShowOption();
        selectedOption++;
    }
    selectedOption = OPTION_COINS;
    PrintVerticalRAM(selectedOption + 5, 26, ">");
}

void TestSaveToEEPROM() {
    struct EepromBlockStruct block;
    block.id = EEPROM_BLOCK;
    block.data[0] = coinsPerPlay;
    block.data[1] = controllers;
    block.data[2] = attractSound;
    block.data[3] = livesPerPlay;
    EepromWriteBlock(&block);
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
        case OPTION_LIVES:
            livesPerPlay++;
            if(livesPerPlay == 6) {
                livesPerPlay = 2;
            }
            break;
        default:
            // Save to eeprom
            TestSaveToEEPROM();
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
        case OPTION_LIVES:
            PrintU8Vertical(8, 1, livesPerPlay);
            break;
        default:
            return;
    }
}

void TestUpdate() {
    // Change option / Show button pressed
    if(inputs[0] & BTN_START) {
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

    // Input tests
    SetTile(18, 17, inputs[0] & BTN_LEFT ? 1 : 0);
    SetTile(18, 9, inputs[1] & BTN_LEFT ? 1 : 0);
    SetTile(19, 17, inputs[0] & BTN_UP ? 1 : 0);
    SetTile(19, 9, inputs[1] & BTN_UP ? 1 : 0);
    SetTile(20, 17, inputs[0] & BTN_RIGHT ? 1 : 0);
    SetTile(20, 9, inputs[1] & BTN_RIGHT ? 1 : 0);
    SetTile(21, 17, inputs[0] & BTN_DOWN ? 1 : 0);
    SetTile(21, 9, inputs[1] & BTN_DOWN ? 1 : 0);
    SetTile(22, 17, inputs[0] & BTN_A ? 1 : 0);
    SetTile(22, 9, inputs[1] & BTN_A ? 1 : 0);
    SetTile(23, 17, inputs[1] & BTN_SL ? 1 : 0);
    SetTile(23, 9, inputs[1] & BTN_SR ? 1 : 0);
    SetTile(24, 17, inputs[0] & BTN_START ? 1 : 0);
    SetTile(24, 9, inputs[0] & BTN_SELECT ? 1 : 0);
}
