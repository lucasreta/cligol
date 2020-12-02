# cligol

Command-line interface Game of Life.

## Compilation

Run the following command:

```
gcc -o cligol main.c
```

## Usage

It has three simple modes of use: file-only, display and control. These modes 
can be accesed by passing parameters to the executable.

### File-only

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

