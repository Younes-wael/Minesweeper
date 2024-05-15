// Spielfald.cpp - Implementation of functions
#include <iostream>

#include <iomanip>

#include "spielfald.h"

#include "random.h" // Assuming getRandom function for mine placement

#include <array>

using namespace std;

// Declaration of the game board
array < array < Tile, 12 > , 12 > Spielfeld;

// Function to calculate the number of mines around a specific tile
int Hils(int x, int y, array < array < Tile, 12 > , 12 > board) {
    int mines_around = 0;
    int c_tocheck = 0;
    int r_tocheck = 0;
    // Loop to check the tiles surrounding the given coordinates
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {

            c_tocheck = x + i;
            r_tocheck = y + j;
            // Avoid checking the tile itself
            if (i == 0 && j == 0) continue;
            // Check for valid coordinates and count neighboring mines
            if (c_tocheck >= 0 && c_tocheck < 12 && r_tocheck < 12 && r_tocheck >= 0 && board[c_tocheck][r_tocheck].alloc == Allocation::mine)
                mines_around++;

        }
    }

    return mines_around;
}
// Function to initialize the game board with mines and their counts
void initialize(int mines_onfield) {
    // Clear the game board
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            Spielfeld[i][j].alloc = Allocation::hidden;
            Spielfeld[i][j].summ_mines_around = 0;
        }
    }
    // Place mines randomly on the board
    int mine_pos_colm = 0;
    int mine_pos_row = 0;

    for (int i = 0; i < mines_onfield; i++) {
        do {

            mine_pos_colm = getRandom(0, 11);
            mine_pos_row = getRandom(0, 11);

        } while (Spielfeld[mine_pos_colm][mine_pos_row].alloc == Allocation::mine);
        Spielfeld[mine_pos_colm][mine_pos_row].alloc = Allocation::mine;
    }
    // Calculate and set the number of neighboring mines for each non-mine tile
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            if (Spielfeld[i][j].alloc != Allocation::mine) {
                Spielfeld[i][j].summ_mines_around = Hils(i, j, Spielfeld);
            }
        }
    }

}
void display(bool boolean) {

    int row = 0;
    for (int i = 0; i < 12; i++) {
        row++;
        // Display the row number and separator
        cout << setw(2) << setfill('0') << row << "| ";
        // If boolean is false, display hidden mines tiles
        if (boolean == false) {
            // Display each tile based on its allocation status
            for (int j = 0; j < 12; j++) {
                // Display mines
                if (Spielfeld[i][j].alloc == Allocation::mine) cout << " X ";
                // Display hidden tiles
                else if (Spielfeld[i][j].alloc == Allocation::hidden) cout << " * ";
                // Display flagged tiles
                else if (Spielfeld[i][j].alloc == Allocation::flagged) cout << " ! ";
                // Display revealed empty tiles
                else if (Spielfeld[i][j].alloc == Allocation::revealed and Spielfeld[i][j].summ_mines_around == 0) cout << " . ";
                // Display revealed tiles with mine count
                else cout << " " << Spielfeld[i][j].summ_mines_around << " ";

            }
        }
        // If boolean is true, display revealed tiles with their mine counts
        else{
            // Display each revealed tile based on its mine count or as an empty tile, or unreaveled tile
            for (int j = 0; j < 12; j++) {
                // Display revealed tile with mine count
                if (Spielfeld[i][j].alloc == Allocation::revealed and Spielfeld[i][j].summ_mines_around != 0)
                    cout << " " << Spielfeld[i][j].summ_mines_around << " ";
                // Display flagged tiles
                else if (Spielfeld[i][j].alloc == Allocation::flagged) cout << " ! ";
                // Display revealed empty tile
                else if (Spielfeld[i][j].alloc == Allocation::revealed and Spielfeld[i][j].summ_mines_around == 0) cout << " . ";
                // Display unrevealed tiles
                else cout << " * ";

            }
        }
        cout << endl;

    }

    // Display the bottom separator and column numbers
    cout << "    -----------------------------------" << endl;
    cout << "   ";
    for (int j = 0; j < 12; j++) {
        cout << " " << j + 1 << " ";
    }
    cout << endl;
};
/*
// Function to display the game board based on game-on(true)  or game-over(false)
void display(bool boolean) {
    // If boolean is false, display hidden mines tiles

        int row = 0;
        for (int i = 0; i < 12; i++) {
            row++;
            // Display the row number and separator
            cout << setw(2) << setfill('0') << row << "| ";
             if (boolean == false) {
            // Display each tile based on its allocation status
            for (int j = 0; j < 12; j++) {
                // Display mines
                if (Spielfeld[i][j].alloc == Allocation::mine) cout << " X ";
                // Display hidden tiles
                else if (Spielfeld[i][j].alloc == Allocation::hidden) cout << " * ";
                // Display revealed empty tiles
                else if (Spielfeld[i][j].alloc == Allocation::revealed && Spielfeld[i][j].summ_mines_around == 0) cout << " . ";
                // Display revealed tiles with mine count
                else cout << " " << Spielfeld[i][j].summ_mines_around << " ";

            }
             }
             // If boolean is true, display revealed tiles with their mine counts
             else {
                // Display each revealed tile based on its mine count or as an empty tile, or unreaveled tile
                for (int j = 0; j < 12; j++) {
                    // Display revealed tile with mine count
                    if (Spielfeld[i][j].alloc == Allocation::revealed && Spielfeld[i][j].summ_mines_around != 0)
                        cout << " " << Spielfeld[i][j].summ_mines_around << " ";
                    // Display revealed empty tile
                    else if (Spielfeld[i][j].alloc == Allocation::revealed && Spielfeld[i][j].summ_mines_around == 0) cout << " . ";
                    // Display unrevealed tiles
                    else cout << " * ";

                }}
            cout << endl;
        }

        // Display the bottom separator and column numbers
        cout << "    -----------------------------------" << endl;
        cout << "   ";
        for (int j = 0; j < 12; j++) {
            cout << " " << j + 1 << " ";
        }
        cout << endl;





};*/



// Function to check if there are revealed empty neighboring tiles
bool revealedEmptyNeighbour(int x, int y) {

    int c_tocheck = 0;
    int r_tocheck = 0;

    // Loop through neighboring tiles to find revealed empty ones
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {

            c_tocheck = x + i;
            r_tocheck = y + j;

            // Skip the tile being checked and only check revealed empty neighbors
            if (i == 0 && j == 0) continue;

            // Check if the neighboring tile is within bounds, revealed, and has no neighboring mines
            if (c_tocheck >= 0 && c_tocheck < 12 && r_tocheck < 12 && r_tocheck >= 0 &&
                Spielfeld[c_tocheck][r_tocheck].alloc == Allocation::revealed && Spielfeld[c_tocheck][r_tocheck].summ_mines_around == 0)
                // Found a revealed empty neighboring tile
                return true;

        }
    }
    // No revealed empty neighboring tile found
    return false;

}

// Function to check and reveal neighboring tiles with no neighboring mines
bool checkNeighbours() {

    // Loop through all tiles on the board
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            // Check if the tile is hidden and has revealed empty neighbors
            if (Spielfeld[i][j].alloc == Allocation::hidden && revealedEmptyNeighbour(i, j)) {
                // Reveal the tile
                Spielfeld[i][j].alloc = Allocation::revealed;
                // Return true to indicate a tile was revealed
                return true;
            }
        }
    }
    // No hidden tile with revealed empty neighbors found
    return false;
}
