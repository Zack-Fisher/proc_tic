#include "input_logic.h"

// there are some cross cutting concerns in the modules, this is fine.
// logic modules should be stateless interfaces, this doesn't violate that.
#include "game_logic.h"

void input_init(AppState* appState)
{

}

void input_loop(AppState* appState)
{ // input loop
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                appState->isRunning = 0;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    appState->isRunning = 0;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;

                    put_piece(appState->board, appState->player, mouseX / (WIDTH / 3), mouseY / (HEIGHT / 3));

                    if (appState->player == X) {
                        appState->player = O;
                    } else {
                        appState->player = X;
                    }
                }
                break;
        }
    }
}

void input_cleanup(AppState* appState)
{

}
