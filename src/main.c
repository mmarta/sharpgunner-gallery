#include "system/machine.h"
#include "modes/game.h"
#include "modes/title.h"
#include "modes/test.h"

int main() {
    MachineSetup();
    MachineCrossHatch();
    MachineInitHi();
    TitleStart();

    while(1) {
        WaitVsync(1);

        switch(machineMode) {
            case GAME:
                GameUpdate();
                if(machineMode == TITLE) {
                    TitleStart();
                }
                break;
            case TITLE:
                TitleUpdate();
                break;
            case TEST:
                TestUpdate();
                if(machineMode == TITLE) {
                    credits = 0;
                    MachineCrossHatch();
                    MachineInitHi();
                    TitleStart();
                }
                break;
        }

        if(!MachineInput()) {
            TestInit();
        }
    }

    return 0;
}
