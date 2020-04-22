#include "machine.h"

u8 credits = 0;
MachineMode machineMode = TITLE;
u32 hi = 10000;

u8 coinSwitchDown = false;
int inputs[] = { 0, 0 };

void MachineSetup() {
    srand(GetTrueRandomSeed());

    SetTileTable(tiles);
    ClearVram();

    PrintVerticalRAM(31, 18, "CREDITS");
    PrintU8Vertical(31, 9, credits);

    SetTile(0, 13, 71);
    SetTile(0, 14, 70);
    PrintU32Vertical(1, 11, hi, 9999999);
}

void MachineInput() {
    // Read inputs (unrolled)
    inputs[0] = ReadJoypad(0);
    inputs[1] = ReadJoypad(1);

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
                    PrintU8Vertical(31, 9, credits);
                }
            }
            coinSwitchDown = true;
        }
    } else if(coinSwitchDown) {
        coinSwitchDown = false;
    }
}
