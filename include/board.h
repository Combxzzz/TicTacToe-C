#ifndef BOARD_H
#define BOARD_H
#include <stdbool.h>

enum Sizes {
    BOARD_SIDE_SIZE = 3,
    VALID_DIAGONALS_ON_BOARD = 2,
    BOARD_SIZE = 9
};

enum MoveResult {
    MOVE_SUCCESS,
    MOVE_ERR_INVALID_SYMBOL,
    MOVE_ERR_POSITION_OUT_OF_BOUNDS,
    MOVE_ERR_POSITION_OCCUPIED,
    MOVE_ERR_POSITION_INVALID
};

enum PositionAvailability {
    POSITION_AVAILABLE,
    POSITION_OCCUPIED,
    POSITION_INVALID
};

enum Symbols {
    SYMBOL_X = 'x',
    SYMBOL_O = 'o',
};

enum GameState {
    GAME_STATE_X_WIN,
    GAME_STATE_O_WIN,
    GAME_STATE_PLAYING,
    GAME_STATE_DRAW
};

enum Memory {
    MEMORY_SUCCESS,
    MEMORY_FAILED
};


struct Board {
    char cells[BOARD_SIZE];
};

struct Board board_init();

enum Memory reset_board(struct Board **board);

void print_board(const struct Board *board);

enum PositionAvailability is_position_valid(const struct Board *board, int position);

enum MoveResult make_move(struct Board *board, int position, enum Symbols symbol);

enum GameState check_winner(const struct Board *board);

bool is_full(const char *cells);

enum GameState check_occurrences(const char *sequence, int breakpoint);

enum GameState verify_lines(const char *cells);
enum GameState verify_columns(const char *cells);
enum GameState verify_diagonals(const char *cells);

#endif
