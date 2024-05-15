// Spielfeld.h - Header file containing declarations

#include <array>
using namespace std;

// Enum to represent the state of each tile on the game board
enum Allocation {
    hidden,     // Tile not yet revealed
    revealed,   // Tile revealed
    mine  ,      // Tile contains a mine
    flagged
};

// Structure to represent a tile on the game board
struct Tile {
    Allocation alloc;           // State of the tile
    int summ_mines_around;     // Number of mines around this tile
};

// Declaration of the game board as a 12x12 grid of tiles
extern array<array<Tile, 12>, 12> Spielfeld;

// Function declarations
int Hils(int x, int y, array < array < Tile, 12 > , 12 > board);
void initialize(int mines_onfield);                     // Initialize the game board
void display(bool boolean);                             // Display the game board
bool revealedEmptyNeighbour(int x, int y);              // Check for revealed empty neighbors
bool checkNeighbours();                                 // Check and reveal neighboring empty tiles
bool Nutzereingabe(int x, int y);                       // Validate user input
