#pragma once

#include <SDL2/SDL.h>

#define WIDTH 600
#define HEIGHT 600

#define EMPTY 0
#define X 1
#define O 2
#define TIE 3

typedef struct {
    int isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;
    // this way, the state of the array is auto-malloced with the struct and auto-freed with the struct.
    // easier to manage, esp if we know the layout of the array already.
    int board[9];
    int player;
    int winner;
} AppState;
