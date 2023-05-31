#pragma once

#include "../defines.h"

// actual special public functions.
// allow the other modules to "play" the game through the interface.
// for example, the input needs to call this function directly if we don't want to do a messy input state callback system.
int put_piece(int* board, int piece, int x, int y);

void game_init(AppState* appState);
void game_loop(AppState* appState);
void game_cleanup(AppState* appState);
