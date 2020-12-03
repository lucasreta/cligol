# cligol

Command-line interface Game of Life.


## Compilation

Run the following command:

```
gcc -o cligol main.c
```

Specs of my gcc version:

```
Using built-in specs.
COLLECT_GCC=gcc
Target: x86_64-linux-gnu
Thread model: posix
gcc version 8.3.0 (Debian 8.3.0-6) 
```


## Configuration

Before compilation, you can configure the four variables defined in `headers/config.h`
to adjust the behaviour of the program.

- `BOARD_HEIGHT (int)`: defines number of rows in the board.
- `BOARD_WIDTH (int)`: defines number of columns in the board.
- `TOROIDAL (int)`: set to 1, the board behaves as a toroidal surface. Otherwise the 
edges of the board represent a limit beyond which nothing exists.
- `FILENAME (string)`: name of file to use for reading and storing game data.

## Usage

It has three simple modes of use: _file-only_, _display_ and _control_. These modes 
can be accesed by passing parameters to the executable.



### File-only (default)

```
./cligol
```

The file-only mode iterates through the board and updates it to the next turn,
saving the result in the file `data/board.txt`, without displaying anything to
the user.


### Display

```
./cligol 1
```

If you pass one parameter with a value of 1, the display mode updates the board 
to the next turn and outputs the result to the console before updating the data 
file.


### Control

```
./cligol 1 1
```

If you pass two parameters with a value of 1, you activate the Control mode, 
which lets you iterate through as many rounds as you want before quitting the 
game and saving the data.


