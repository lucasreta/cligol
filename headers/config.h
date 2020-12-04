#include <stdio.h>

#define BOARD_HEIGHT 7
#define BOARD_WIDTH 52
#define TOROIDAL 1
#define FILENAME "cligol/data/board.txt"

struct t_board { int grid[BOARD_HEIGHT][BOARD_WIDTH]; };
