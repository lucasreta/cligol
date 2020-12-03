#include "headers/config.h"
#include "headers/custom_string.h"

void compute (int N[BOARD_HEIGHT][BOARD_WIDTH], int Z[BOARD_HEIGHT][BOARD_WIDTH]);

void randomize (int N[BOARD_HEIGHT][BOARD_WIDTH]);

void clear () { printf ("\033[H\033[J"); }

void show (int Z[BOARD_HEIGHT][BOARD_WIDTH]);

void move (int current_board[BOARD_HEIGHT][BOARD_WIDTH]);

void display_loop (struct t_board *board, int controllable);

void file_write (int board[BOARD_HEIGHT][BOARD_WIDTH]);

struct t_board file_read_or_create ();

int main (int c, char **v)
{
    struct t_board board = file_read_or_create ();
    int display = (c > 1) ? atoi (v[1]) : 0;
    int controllable = (c > 2) ? atoi (v[2]) : 0;
    if (display != 1)
    {
        move (board.grid);
    }
    else
    {
        display_loop (&board, controllable);
    }
    file_write (board.grid);
    return 0;
}

// Storage functions
void file_write (int board[BOARD_HEIGHT][BOARD_WIDTH])
{
    FILE *f = fopen (FILENAME, "w");
    int i, j;
    for (i = 0; i < BOARD_HEIGHT; i++)
    {
        if (i != 0) {
            fprintf (f, "\n");
        }
        for (j = 0; j < BOARD_WIDTH; j++)
        {
            if (j + 1 < BOARD_WIDTH)
            {
                fprintf (f, "%d ", board[i][j]);
            }
            else
            {
                fprintf (f, "%d", board[i][j]);
            }
        }
    }
    fclose (f);
}

struct t_board file_read_or_create ()
{
    struct t_board board = {{{0}}};

    FILE *f = fopen (FILENAME, "r");
    if (f == NULL)
    {
        randomize (board.grid);
        file_write (board.grid);
        f = fopen (FILENAME, "r");
    }

    int line = 0;
    char input[BOARD_WIDTH * 2 + 1] = "";

    while (BOARD_HEIGHT > line && fgets (input, sizeof input, f))
    {
        char** values;
        if ((values = split (input, " ")))
        {
            int cell = 0;
            for (char **p = values; *p; p++, cell++)
            {
                remove_trailing_newline (*p);
                board.grid[line][cell] = atoi (*p);
                free (*p);
            }
            free (values);
        }
        line++;
    }
    fclose (f);

    return board;
}

// Game functions
void compute (int neighbors[BOARD_HEIGHT][BOARD_WIDTH], int board[BOARD_HEIGHT][BOARD_WIDTH])
{
    int i,j;
    for (i = 0; i < BOARD_HEIGHT; i++)
    {
        for (j = 0; j < BOARD_WIDTH; j++)
        {
            if (TOROIDAL != 0)
            {
                int top, left, right, bottom;
                top = (i - 1 < 0) ? BOARD_HEIGHT - 1 : i - 1;
                left = (j - 1 < 0) ? BOARD_WIDTH - 1 : j - 1;
                right = (j + 1 >= BOARD_WIDTH) ? 0 : j + 1;
                bottom = (i + 1 >= BOARD_HEIGHT) ? 0 : i + 1;
                neighbors[i][j] = board[top][left] + board[i][left] + board[bottom][left]
                        + board[top][j] + board[bottom][j]
                        + board[top][right] + board[i][right] + board[bottom][right];
            }
            else
            {
                neighbors[i][j] = board[i-1][j-1] + board[i][j-1] + board[i+1][j-1]
                        + board[i-1][j] + board[i+1][j]
                        + board[i-1][j+1] + board[i][j+1] + board[i+1][j+1];
            }
        }
    }

}

void randomize (int board[BOARD_HEIGHT][BOARD_WIDTH])
{
    int i,j;
    for (i = 0; i < BOARD_HEIGHT; i++)
    {
        for (j = 0; j < BOARD_WIDTH; j++)
        {
            board[i][j] = rand() % 2;
        }
    }

}

void show (int Z[BOARD_HEIGHT][BOARD_WIDTH])
{
    int i,j;
    for (i = 0; i < BOARD_HEIGHT; i++)
    {
        for (j = 0; j < BOARD_WIDTH; j++)
        {
            if (Z[i][j] == 0)
                printf ("- ");
            else
                printf ("X ");
        }
        printf ("\n");
    }

}

void move (int current_board[BOARD_HEIGHT][BOARD_WIDTH])
{
    int i, j;
    int future_board[BOARD_HEIGHT][BOARD_WIDTH]= {{0}};
    compute (future_board, current_board);

    for (i = 0; i < BOARD_HEIGHT; i++)
    {
        for (j = 0; j < BOARD_WIDTH; j++)
        {
            if ((current_board[i][j] == 1) && (future_board[i][j] < 2 || future_board[i][j] > 3))
            {
                current_board[i][j] = 0;
            }
            else if ((current_board[i][j] == 0) && (future_board[i][j] == 3))
            {
                current_board[i][j] = 1;
            }
        }
    }

}

void display_loop (struct t_board *board, int controllable)
{
    int control = 0;
    if (controllable == 1)
    {
        clear ();
        show (board->grid);
        printf ("Press 0 to continue, other key to exit: ");
        int read = scanf ("%d", &control);
        if (read != 1) control = 1;
    }
    while (control == 0)
    {
        clear ();
        move (board->grid);
        show (board->grid);
        if (controllable == 1)
        {
            printf ("Press 0 to continue, other key to exit: ");
            int read = scanf ("%d", &control);
            if (read != 1) control = 1;
        }
        else
        {
            control = 1;
        }
    }
}
