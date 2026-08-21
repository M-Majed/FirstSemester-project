# Minesweeper Console Game

A C++ console-based implementation of the classic Minesweeper game. This project was developed as a first semester programming project and includes gameplay mechanics, user accounts, and persistent save functionality.

## Features

- Classic Minesweeper gameplay
- Random bomb generation
- Automatic mine count calculation
- Cell discovery and recursive empty-area expansion
- Flag placement and removal
- Win and game-over detection
- Multiple difficulty levels:
  - Easy: 9x9 board with 10 bombs
  - Normal: 16x16 board with 40 bombs
  - Hard: 16x30 board with 99 bombs
  - Custom board configuration
- User registration and login
- Password change support
- Three save slots
- Load previous games
- Optional autosave functionality

## Build and Run

### Linux / macOS

```bash
g++ projectfinal.cpp -o minesweeper
./minesweeper
```

### Windows (MinGW)

```bash
g++ projectfinal.cpp -o minesweeper.exe
minesweeper.exe
```

## Gameplay Controls

```
1 - Discover a cell
2 - Place a flag
3 - Remove a flag
4 - Save game
5 - Exit
```

Coordinates are entered using:

```
row column
```

## Project Structure

```
.
├── projectfinal.cpp
└── README.md
```

## Implementation Details

The game maintains two boards:

- Real board: stores bombs and calculated values.
- Hidden board: represents the player's visible progress.

The first move is protected by regenerating the board if the selected location contains a bomb.

## Future Improvements

- Refactor code into object-oriented classes
- Replace text-file storage with a database
- Add encrypted password storage
- Add graphical user interface
- Improve input validation

## License

This project is intended for educational purposes.
