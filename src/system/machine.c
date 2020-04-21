#include "machine.h"

u8 credits = 0;
MachineMode machineMode = GAME;
u32 hi = 10000;

u8 coinSwitchDown = false;

void MachineSetup() {
    srand(GetTrueRandomSeed());

    SetTileTable(tiles);
    ClearVram();

    PrintVerticalRAM(31, 17, "CREDITS");
    PrintU8Vertical(31, 8, credits);

    SetTile(0, 13, 71);
    SetTile(0, 14, 70);
    PrintU32Vertical(1, 11, hi, 9999999);
}

void MachineInput() {
    int inputs[] = {
        ReadJoypad(0),
        ReadJoypad(1)
    };

    // Test switch
    if(inputs[0] && BTN_SR) {
        // Go into test mode
    }

    // Coin/Service
    if(inputs[0] & BTN_SL || inputs[1] & BTN_SL || inputs[1] & BTN_SR) {
        if(!coinSwitchDown) {
            if(credits < 9) {
                credits++;
                if(machineMode != GAME) {
                    PrintU8Vertical(31, 8, credits);
                }
            }
            coinSwitchDown = true;
        }
    } else if(coinSwitchDown) {
        coinSwitchDown = false;
    }
}
