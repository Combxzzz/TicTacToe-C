#include <stdio.h>
#include "board.h"

#include <stdlib.h>

struct Board board_init() {
    return (struct Board) {
        .cells = {
            '1', '2', '3',
            '4', '5', '6',
            '7', '8', '9'
        }
    };
}

void print_board(const struct Board *board) {
    const char *cells = board->cells;

    printf(" %c | %c | %c\n", cells[0], cells[1], cells[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", cells[3], cells[4], cells[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", cells[6], cells[7], cells[8]);
}

enum PositionAvailability is_position_valid(const struct Board *board, int position) {
    if (position < 1 || position > 9) {
        printf("Invalid position");
        return POSITION_INVALID;
    }

    position--;
    const char *cells = board->cells;

    if (cells[position] == SYMBOL_X || cells[position] == SYMBOL_O) {
        return POSITION_OCCUPIED;
    }

    return POSITION_AVAILABLE;
}

enum MoveResult make_move(struct Board *board, int position, const enum Symbols symbol) {
    if (symbol != SYMBOL_X && symbol != SYMBOL_O) {
        return MOVE_ERR_INVALID_SYMBOL;
    }

    if (position < 1 || position > 9) {
        return MOVE_ERR_POSITION_OUT_OF_BOUNDS;
    }

    const enum PositionAvailability available = is_position_valid(board, position);

    if (available != POSITION_AVAILABLE) {
        return available == POSITION_OCCUPIED
        ? MOVE_ERR_POSITION_OCCUPIED
        : MOVE_ERR_POSITION_INVALID;
    }

    position--;
    char *cells = board->cells;

    cells[position] = symbol;
    return MOVE_SUCCESS;
}

enum GameState check_occurrences(const char *sequence, const int breakpoint) {
    int x_occurrences = 0;
    int o_occurrences = 0;

    for (int i = 0; i < breakpoint; i++) {
        const char current = sequence[i];

        if (current == SYMBOL_X) {
            x_occurrences++;
        } else if (current == SYMBOL_O) {
            o_occurrences++;
        }
    }

    if (x_occurrences == 3) {
        return GAME_STATE_X_WIN;
    }
    if (o_occurrences == 3) {
        return GAME_STATE_O_WIN;
    }

    return GAME_STATE_PLAYING;
}

enum GameState check_winner(const struct Board *board) {
    const char *cells = board -> cells;

    const enum GameState lines_state = verify_lines(cells);
    if (lines_state == GAME_STATE_X_WIN || lines_state == GAME_STATE_O_WIN) {
        return lines_state;
    }

    const enum GameState columns_state = verify_columns(cells);
    if (columns_state == GAME_STATE_X_WIN || columns_state == GAME_STATE_O_WIN) {
        return columns_state;
    }

    const enum GameState diagonals_state = verify_diagonals(cells);
    if (diagonals_state == GAME_STATE_X_WIN || diagonals_state == GAME_STATE_O_WIN) {
        return diagonals_state;
    }

    if (is_full(cells)) {
        return GAME_STATE_DRAW;
    }

    return GAME_STATE_PLAYING;
}

enum GameState verify_lines(const char *cells) {
    const char lines[BOARD_SIDE_SIZE][BOARD_SIDE_SIZE] = {
        {cells[0], cells[1], cells[2]},
        {cells[3], cells[4], cells[5]},
        {cells[6], cells[7], cells[8]}
    };

    for (int i = 0; i < BOARD_SIDE_SIZE; i++) {
        const char *current_line = lines[i];

        const enum GameState game_state = check_occurrences(current_line, BOARD_SIDE_SIZE);

        if (game_state == GAME_STATE_X_WIN || game_state == GAME_STATE_O_WIN) {
            return game_state;
        }
    }

    return GAME_STATE_PLAYING;
}

enum GameState verify_columns(const char *cells) {
    const char columns[BOARD_SIDE_SIZE][BOARD_SIDE_SIZE] = {
        {cells[0], cells[3], cells[6]},
        {cells[1], cells[4], cells[7]},
        {cells[2], cells[5], cells[8]}
    };

    for (int i = 0; i < BOARD_SIDE_SIZE; i++) {
        const char *current_column = columns[i];

        const enum GameState game_state = check_occurrences(current_column, BOARD_SIDE_SIZE);

        if (game_state == GAME_STATE_X_WIN || game_state == GAME_STATE_O_WIN) {
            return game_state;
        }
    }

    return GAME_STATE_PLAYING;
}

enum GameState verify_diagonals(const char *cells) {
    const char diagonals[2][BOARD_SIDE_SIZE] = {
        {cells[0], cells[4], cells[8]},
        {cells[6], cells[4], cells[2]}
    };

    for (int i = 0; i < VALID_DIAGONALS_ON_BOARD; i++) {
        const char *current_diagonal = diagonals[i];

        const enum GameState game_state = check_occurrences(current_diagonal, BOARD_SIDE_SIZE);

        if (game_state == GAME_STATE_X_WIN || game_state == GAME_STATE_O_WIN) {
            return game_state;
        }
    }

    return GAME_STATE_PLAYING;
}

enum Memory reset_board(struct Board **board) {
    struct Board *new_board = malloc(sizeof(struct Board));

    if (new_board == NULL) {
        return MEMORY_FAILED;
    }

    *new_board = board_init();

    free(*board);
    *board = new_board;

    return MEMORY_SUCCESS;
}

bool is_full(const char *cells) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (cells[i] == SYMBOL_X || cells [i] == SYMBOL_O) {
            continue;
        }

        return false;
    }

    return true;
}
