#include "system/machine.h"
#include "modes/game.h"
#include "modes/title.h"

int main() {
    MachineSetup();
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
        }

        MachineInput();
    }

    return 0;
}
