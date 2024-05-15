#include <iostream>

#include "spielfald.h"

#include <array>

using namespace std;


// Function to validate user input for revealing a tile
bool Nutzereingabe(int x, int y) {
    // Check if the selected tile is not a mine
    if (Spielfeld[x - 1][y - 1].alloc != Allocation::mine)
        // Valid user input, can reveal the tile
        return true;
    // Invalid user input, tile is a mine
    else return false;
}

int main() {
    // Initialize the game with 17 mines and display the initial state
    initialize(17);
    display(true);
    cout << endl;

    int zeile, spalte; // Variables for user input (row and column)
    int verdeckte_felder = 0; // Count of hidden tiles
    char fa;
    do {
        // Prompt the user for their next move
        cout << "Bitte geben Sie nun Ihren naechsten Zug ein." << endl;
        do {
            // Ask the user to input row and column numbers (1-12)
            cout << "Zeile (1-12) _Leerzeichen_ Spalte (1-12):" << endl;
            cin >> zeile >> spalte;

            // Ensure the user input is within the game board bounds
        } while (zeile <= 0 or zeile > 12 or spalte <= 0 or spalte > 12);
        // flagged or revealed
        do{
        cout << "Willst du flaggen (f) oder aufdecken (a)?" << endl;
        cin>>fa;
        }while(fa!='f' and fa!='a');
        if(fa=='f' and Spielfeld[zeile - 1][spalte - 1].alloc != Allocation::flagged){
        Spielfeld[zeile - 1][spalte - 1].alloc = Allocation::flagged;
        }
        else if (fa=='f' and Spielfeld[zeile - 1][spalte - 1].alloc == Allocation::flagged){
        Spielfeld[zeile - 1][spalte - 1].alloc = Allocation::hidden;
        }
        // If the selected tile is not a mine, reveal it and its neighbors with no neighboring mines
        if (Spielfeld[zeile - 1][spalte - 1].alloc != Allocation::mine and fa=='a') {
            Spielfeld[zeile - 1][spalte - 1].alloc = Allocation::revealed;
            // Continuously reveal tiles neighboring revealed tiles with no neighboring mines until there are none left
            do {
                checkNeighbours();
            } while (checkNeighbours());
        }


        // Count the remaining hidden tiles
        verdeckte_felder = 0;
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 12; j++) {
                if (Spielfeld[i][j].alloc == Allocation::hidden)
                    verdeckte_felder++;
            }
        }

        // Display the count of remaining hidden tiles and the updated game board
        cout << "Verbleibende verdeckte Felder: " << verdeckte_felder << endl;
        display(true);

        // Continue the game if the user input is valid and there are hidden tiles (that are not mines) remaining
    } while (Nutzereingabe(zeile, spalte) and verdeckte_felder != 0);

    // Display game outcome based on the number of remaining hidden tiles
    if (verdeckte_felder != 0) {

        cout << endl << endl << "******BOOOOOM******" << endl << "Leider verloren." << endl << endl;
         cout << endl<<"Verbleibende verdeckte Felder: " << verdeckte_felder << endl;
        display(false); // Display the final state of the game
    } else {
        cout << "Congratulations you won!!"; // Player wins if there are no hidden tiles (that are not mines) remaining
    }

    return 0;
}
