#include <stdio.h>
#include <SDL2/SDL.h>

#define WIDTH 600
#define HEIGHT 600

#define EMPTY 0
#define X 1
#define O 2

typedef struct {
    int isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;
    // this way, the state of the array is auto-malloced with the struct and auto-freed with the struct.
    // easier to manage, esp if we know the layout of the array already.
    int board[9];
    int player;
} AppState;

const int winning_combinations[8][3] = {
    {0, 1, 2}, // top row
    {3, 4, 5}, // middle row
    {6, 7, 8}, // bottom row
    {0, 3, 6}, // left column
    {1, 4, 7}, // middle column
    {2, 5, 8}, // right column
    {0, 4, 8}, // left diagonal
    {2, 4, 6}  // right diagonal
};

void pretty_print_board(int* board)
{
    printf("\n");
    printf(" %d | %d | %d \n", board[0], board[1], board[2]);
    printf("---+---+---\n");
    printf(" %d | %d | %d \n", board[3], board[4], board[5]);
    printf("---+---+---\n");
    printf(" %d | %d | %d \n", board[6], board[7], board[8]);
    printf("\n");
}

int has_won(int* board)
{
    for (int i = 0; i < 8; i++)
    {
        const int* combination = winning_combinations[i];
        int a = combination[0];
        int b = combination[1];
        int c = combination[2];

        if (board[a] != 0 && board[a] == board[b] && board[b] == board[c])
        {
            // return one of the winning player's pieces.
            return board[a];
        }
    }

    // nobody has won.
    // false.
    return EMPTY;
}

int put_piece(int* board, int piece, int x, int y)
{
    if (x < 0 || x > 2 || y < 0 || y > 2)
    {
        return 0;
    }

    if (board[y * 3 + x] != EMPTY)
    {
        return 0;
    }

    // mutate the passed board pointer directly.
    board[y * 3 + x] = piece;

    pretty_print_board(board);

    // could put a piece, return true.
    return 1;
}

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


int main()
{
    AppState* appState = (AppState*)malloc(sizeof(AppState));
    appState->isRunning = 1;
    appState->player = X;

    { // init

        { // game init
            for (int i = 0; i < 9; i++) {
                appState->board[i] = EMPTY;
            }
        }

        { // init SDL
            SDL_Init(SDL_INIT_VIDEO);
            appState->window = SDL_CreateWindow("SDL Input Loop", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
            appState->renderer = SDL_CreateRenderer(appState->window, -1, 0);
        }

    }

    while (appState->isRunning)
    { // main loop
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

        { // game loop
            if (has_won(appState->board) != EMPTY)
            {
                appState->isRunning = 0;
            }
        }

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
    }

    { // cleanup

        printf("Exiting...\n");

        { // exit SDL.
            SDL_DestroyRenderer(appState->renderer);
            SDL_DestroyWindow(appState->window);
            SDL_Quit();
        }

        {
            free(appState);
        }

    }

    return 0;
}
