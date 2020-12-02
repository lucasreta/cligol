#include <stdio.h>

#define BOARD_HEIGHT 10
#define BOARD_WIDTH 10
#define TOROIDAL 1
#define FILENAME "data/board.txt"

struct t_board { int grid[BOARD_HEIGHT][BOARD_WIDTH]; };
