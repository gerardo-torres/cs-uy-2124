/*
Author:         Gerardo Torres
Class:          CS-UY 2124
File Name:      rec03.cpp
-----------------------------------
Description: an implementation of the minesweeper game utilizing
classes, encapsulation, and data hiding.
-----------------------------------
*/

#include <string>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>  // Random header file

using namespace std;

struct Coordinate {
    int row;
    int col;
};

class Minesweeper {
    public:
        Minesweeper() { 
            bool myBool = false;
            int myInt = 0;
            // Initializing the 2D vector
            for (int r = 0; r < ROW; ++r) {
                vector<int> numRow;
                vector<bool> bombRow;
                vector<bool> visibleRow;
                for (int c = 0; c < COL; ++c) {
                    visibleRow.push_back(myBool);
                    bombRow.push_back(myBool);
                    numRow.push_back(myInt);
                }
                layerIsBomb.push_back(bombRow);
                layerIsVisible.push_back(visibleRow);
                layerNumBomb.push_back(numRow);
            }

            // Initializing bombs
            for (int r = 0; r < ROW; ++r) {
                for (int c = 0; c < COL; ++c) {
                    // srand(time(NULL));
                    if ((rand() % 100) < BOMB_PROBABILITY) {
                        layerIsBomb[r][c] = true;
                    } else {
                        layerIsBomb[r][c] = false;
                    }
                }
            }

            // Checking number of neighboring bombs
            for (int r = 0; r < ROW; ++r) {
                for (int c = 0; c < COL; ++c) {
                    // iterating through each tile
                    if (!layerIsBomb[r][c]) {
                        int numBombs = 0;
                        // Checking +/- 1 vertically and horizontaly
                        // For each tile; counting neighboring bombs
                        for (int h = -1; h < 2; ++h) {
                            for (int v = -1; v < 2; ++v) {
                                int newR = r + h;
                                int newC = c + v;
                                if ((validRow(newR)) && (validCol(newC))) {
                                    // bool tileBomb = layerIsBomb[r + h][c + v] == true;
                                    if (layerIsBomb[newR][newC] == true) {
                                        ++numBombs;
                                    }
                                }
                            }
                        }
                        layerNumBomb[r][c] = numBombs;
                    }      
                }
            }

        }

        void display(bool displayBomb) {
            // Display the board; displayBomb is bool if the bombs 
            // should be displayed

            // <-- tile legend -->
            // bomb:               "x"
            // not visible:        "-"
            // visible, n bombs:   "n"

            if (displayBomb) {
                // Display the bombs!
                for (int r = 0; r < ROW; ++r) {
                    for (int c = 0; c < COL; ++c) {
                        if (layerIsBomb[r][c]) {
                            cout << " x";
                        } else {
                            cout << " " << layerNumBomb[r][c];
                        }
                    }
                    cout << "\n\n";
                }
            } else {
                // Don't display the bombs!
                for (int r = 0; r < ROW; ++r) {
                    for (int c = 0; c < COL; ++c) {
                        if (isVisible(r, c)) {
                            cout << " " << layerNumBomb[r][c];
                        } else {
                            cout << " -";
                        }
                    }
                    cout << "\n\n";
                }
            }
        }

        bool done() {
            for (int r = 0; r < ROW; ++r) {
                for (int c = 0; c < COL; ++c) {
                    bool tileVisible = isVisible(r, c);
                    bool tileBomb = layerIsBomb[r][c];
                    if (!tileBomb && !tileVisible) {
                        // The game should be done if and only if all 
                        // the tiles that are not visible are bombs
                        return false;
                    }
                }
            }
            return true;
        }
        
        bool validRow(int row) {
            // Return bool if row is valid
            if ((row >= 0) && (row < ROW)) {
                return true;
            }
            return false;
        }
        
        bool validCol(int column) {
            // Return bool if column is valid
            if ((column >=0) && (column < COL)) {
                return true;
            }
            return false;
        }

        bool isVisible(int row, int col) {
            // Takes a row and column returns if that tile is visible
            return layerIsVisible[row][col];
        }

        bool play(int r, int c) {
            if (layerIsBomb[r][c]) {
                // player dies, end of game
                return false;
            } else if (layerNumBomb[r][c] > 0) {
                // show the num of adjacent bombs
                layerIsVisible[r][c] = true;
            } else {
                // rippling effect
                for (int h = -1; h < 2; ++h) {
                    for (int v = -1; v < 2; ++v) {
                        int newR = r + h;
                        int newC = c + v;
                        if (validRow(newR) && validCol(newC) && !(isVisible(newR, newC))) {
                            layerIsVisible[newR][newC] = true;
                            play(newR, newC);
                        }
                    }
                }
            }
            return true;
        }

    private:
        const int ROW = 10;
        const int COL = 10;
        const int BOMB_PROBABILITY = 10;
        // Representing the game board as layers
        vector<vector<bool>> layerIsVisible;  // Boolean: is tile visible
        vector<vector<bool>> layerIsBomb;  // Boolean: is tile a bomb
        vector<vector<int>> layerNumBomb;  // Int: num of bombs around
};

int main() {
    Minesweeper sweeper;
    sweeper.display(true);
    cout << '\n';
    // Continue until only invisible cells are bombs
    while (!sweeper.done()) {
        sweeper.display(false); // display board without bombs

        int row_sel = -1, col_sel = -1;
        while (row_sel == -1) {
            // Get a valid move
            int r, c;
            cout << "row? ";
            cin >> r;
            if (!sweeper.validRow(r)) {
                cout << "Row out of bounds\n";
                continue;
            }
            cout << "col? ";
            cin >> c;
            if (!sweeper.validCol(c)) {
                cout << "Column out of bounds\n";
                continue;
            }
            if (sweeper.isVisible(r,c)) {
                cout << "Square already visible\n";
                continue;
            }
            row_sel = r;
            col_sel = c;
        }
        // Set selected square to be visible. May effect other cells.
        if (!sweeper.play(row_sel,col_sel)) {
            cout << "Sorry, you died..\n";
            sweeper.display(true); // Final board with bombs shown
            exit(0);
        }
    }
    // Ah! All invisible cells are bombs, so you won!
    cout << "You won!!!!\n";
    sweeper.display(true); // Final board with bombs shown
}
