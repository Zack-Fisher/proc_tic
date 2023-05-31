#include "render_logic.h"

void draw_x(SDL_Renderer* renderer, int x, int y) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(renderer, x, y, x + 200, y + 200);
    SDL_RenderDrawLine(renderer, x + 200, y, x, y + 200);
}

void draw_o(SDL_Renderer* renderer, int x, int y) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderDrawLine(renderer, x + 100, y, x + 100, y + 200);
    SDL_RenderDrawLine(renderer, x, y + 100, x + 200, y + 100);
}


// each module has logic for init, loop, and cleanup.
void render_init(AppState* appState)
{ // init SDL
    SDL_Init(SDL_INIT_VIDEO);
    appState->window = SDL_CreateWindow("SDL Input Loop", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    appState->renderer = SDL_CreateRenderer(appState->window, -1, 0);
}

void render_loop(AppState* appState)
{ // render loop
    SDL_SetRenderDrawColor(appState->renderer, 0, 0, 0, 255);
    SDL_RenderClear(appState->renderer);

    SDL_SetRenderDrawColor(appState->renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(appState->renderer, 0, 200, 600, 200);
    SDL_RenderDrawLine(appState->renderer, 0, 400, 600, 400);
    SDL_RenderDrawLine(appState->renderer, 200, 0, 200, 600);
    SDL_RenderDrawLine(appState->renderer, 400, 0, 400, 600);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (appState->board[i * 3 + j] == X) {
                draw_x(appState->renderer, j * (WIDTH / 3), i * (HEIGHT / 3));
            } else if (appState->board[i * 3 + j] == O) {
                draw_o(appState->renderer, j * (WIDTH / 3), i * (HEIGHT / 3));
            }
        }
    }

    SDL_RenderPresent(appState->renderer);
}

void render_cleanup(AppState* appState)
{ // exit SDL.
    SDL_DestroyRenderer(appState->renderer);
    SDL_DestroyWindow(appState->window);
    SDL_Quit();
}
