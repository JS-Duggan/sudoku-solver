#include <vector>
#include <iostream>
#include <stdexcept>
#include <set>

#ifndef BOARD
#define BOARD

struct Square {
    std::set<int> candidates;
    bool set;
    int val;

    Square() : candidates(std::set<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}) {};
    Square(int v) : set(true), val(v) {};
};

struct Board {
    std::vector<std::vector<Square>> squares;
    std::vector<bool> filled;
    int freeCells;

    Board() {
        squares = std::vector<std::vector<Square>>(9, std::vector<Square>(9));
        freeCells = 81;
    }

    void readInput() {
        int x;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                std::cin >> x;
                if (x < 0 || x > 9) throw std::out_of_range("Input out of range");
                if (x > 0) {
                    squares[i][j] = Square(x);
                    freeCells--;
                }
            }
        }
    }

    void printBoard() {
        std::cout << std::endl;

        for (int i = 0; i < 9; i++) {
            if (i % 3 == 0 && i) {
                for (int k = 0; k < 11; k++) {
                    std::cout << " -";
                }
                std::cout << std::endl;
            }
            for (int j = 0; j < 9; j++) {
                if (j % 3 == 0 && j) std::cout << " |";
                std::cout << " " << squares[i][j].val;
            }
            
            std::cout << std::endl;
        }
    }

    void removeCandidates(int candidate, int i, int j) {
        for (int k = 0; k < 9; k++) {
            /* remove from column */
            if (!squares[k][j].set) {
                squares[k][j].candidates.erase(candidate);
            }
            
            /* remove from row */
            if (!squares[i][k].set) {
                squares[i][k].candidates.erase(candidate);
            }
        }

        /* remove from square */
        int i_square = i - i % 3;
        int j_square = j - j % 3;

        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                if (!squares[i_square + x][j_square + y].set) {
                    squares[i_square + x][j_square + y].candidates.erase(candidate);
                }
            }
        }

    }

    void addCandidates(int candidate, int i, int j) {
        for (int k = 0; k < 9; k++) {
            /* add to column */
            if (!squares[k][j].set) {
                squares[k][j].candidates.insert(candidate);
            }
            
            /* add to row */
            if (!squares[i][k].set) {
                squares[i][k].candidates.insert(candidate);
            }
        }

        /* add to square */
        int i_square = i - i % 3;
        int j_square = j - j % 3;

        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                if (!squares[i_square + x][j_square + y].set) {
                    squares[i_square + x][j_square + y].candidates.insert(candidate);
                }
            }
        }
    }
};

#endif