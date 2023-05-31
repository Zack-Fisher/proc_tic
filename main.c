#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "defines.h"

#include "logic.h"

// this one main function is theoretically the only state module, and therefore the only one allowed to allocate memory and carry state.
// all state in the logic modules should be passed in as arguments.
int main()
{

    /// INIT GLOBALS
    // i think it's purer to just pass in the malloced data rather than letting the function malloc it for us.
    AppState* appState = (AppState*)calloc(1, sizeof(AppState));
    appState->isRunning = 1;
    appState->player = X;
    /// END INIT GLOBALS

    return play_game(appState);

}
