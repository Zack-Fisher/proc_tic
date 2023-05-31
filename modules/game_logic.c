#include "game_logic.h"

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

    // check for tie, all spaces filled.
    for (int i = 0; i < 9; i++)
    {
        if (board[i] == EMPTY) goto not_tie;
    }
    return TIE;

    not_tie:

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

void game_init(AppState* appState)
{ // game init
    for (int i = 0; i < 9; i++) {
        appState->board[i] = EMPTY;
    }
}

void game_loop(AppState* appState)
{ // game loop
    appState->winner = has_won(appState->board);

    if (appState->winner != EMPTY) {
        appState->isRunning = 0;
    }
}

void game_cleanup(AppState* appState)
{
    if (appState->winner == X) {
        printf("X wins!\n");
    } else if (appState->winner == O) {
        printf("O wins!\n");
    } else if (appState->winner == TIE) {
        printf("Nobody wins!\n");
    }
}
