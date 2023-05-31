#include <unistd.h>
#include <stdio.h>

#include "logic.h"

// return status code
int play_game(AppState* appState) {

    printf("Playing a new game!\n");

    { // init

        printf("Init...\n");

        input_init(appState);
        game_init(appState);
        render_init(appState);

    }

    printf("Entering main loop...\n");

    while (appState->isRunning)
    { // main loop

        input_loop(appState);
        game_loop(appState);
        render_loop(appState);

        // 60 fps
        usleep(16667);

    }

    { // cleanup

        printf("Cleanup...\n");

        input_cleanup(appState);
        game_cleanup(appState);
        render_cleanup(appState);

    }

    return 0;

}
