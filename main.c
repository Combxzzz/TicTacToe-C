#include "board.h"

int main(void) {
    const struct Board board = board_init();

    print_board(&board);

    return 0;
}
