#include "system/machine.h"
#include "modes/game.h"

int main() {
    MachineSetup();

    // Todo: change to title/game alternation
    GameStart(1);

    while(1) {
        WaitVsync(1);

        GameUpdate();
    }

    return 0;
}
