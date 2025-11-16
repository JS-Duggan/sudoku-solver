#include <vector>
#include <iostream>
#include <stdexcept>

#ifndef BOARD
#define BOARD

struct Board {
    std::vector<std::vector<int>> squares;
    int freeCells;
    std::vector<bool> filled;

    Board() {
        squares = std::vector<std::vector<int>>(9, std::vector<int>(9));
        filled = std::vector<bool>(81, false);
        freeCells = 81;
    }

    void readInput() {
        int x;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                std::cin >> x;
                if (x < 0 || x > 9) throw std::out_of_range("Input out of range");
                if (x > 0) {
                    filled[i * 8 + j] = true;
                    freeCells--;
                    squares[i][j] = x;
                }
            }
        }
    }

    void printBoard() {
        for (int i = 0; i < 9; i++) {
            if (i % 3 == 0 && i) {
                for (int k = 0; k < 11; k++) {
                    std::cout << " -";
                }
                std::cout << std::endl;
            }
            for (int j = 0; j < 9; j++) {
                if (j % 3 == 0 && j) std::cout << " |";
                std::cout << " " << squares[i][j];
            }
            
            std::cout << std::endl;
        }
    }
};

#endif