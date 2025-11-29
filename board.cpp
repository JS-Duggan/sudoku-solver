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

    void readInput(std::vector<std::set<std::pair<int, int>>> pq) {
        int x;
        std::cout << "Enter board string: \n";
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                std::cin >> x;
                if (x < 0 || x > 9) throw std::out_of_range("Input out of range");
                if (x > 0) {
                    squares[i][j] = Square(x);
                    removeCandidates(x, pq, i, j);
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

    bool removeCandidates(int candidate, std::vector<std::set<std::pair<int,int>>>& pq, int i, int j) {
        for (int k = 0; k < 9; k++) {
            /* remove from column */
            if (!squares[k][j].set) {
                int size = squares[k][j].candidates.size();
                squares[k][j].candidates.erase(candidate);
                if (squares[k][j].candidates.size() == 0) return false;
                if (squares[k][j].candidates.size() < size) {
                    pq[size].erase({k, j});
                    pq[size - 1].insert({k, j});
                }
            }
            
            /* remove from row */
            if (!squares[i][k].set) {
                int size = squares[i][k].candidates.size();
                squares[i][k].candidates.erase(candidate);
                if (squares[i][k].candidates.size() == 0) return false;
                if (squares[i][k].candidates.size() < size) {
                    pq[size].erase({i, k});
                    pq[size - 1].insert({i, k});
                }
            }
        }

        /* remove from square */
        int i_square = i - i % 3;
        int j_square = j - j % 3;

        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                if (!squares[i_square + x][j_square + y].set) {
                    int size = squares[i_square + x][j_square + y].candidates.size();
                    squares[i_square + x][j_square + y].candidates.erase(candidate);
                    if (squares[i_square + x][j_square + y].candidates.empty()) return false;
                    if (squares[i_square + x][j_square + y].candidates.size() < size) {
                    pq[size].erase({i_square + x, j_square + y});
                    pq[size - 1].insert({i_square + x, j_square + y});
                }
                }
            }
        }

        return true;
    }

    void addCandidates(int candidate, std::vector<std::set<std::pair<int,int>>>& pq, int i, int j) {
        for (int k = 0; k < 9; k++) {
            /* add to column */
            if (!squares[k][j].set && checkCandidate(candidate, k, j)) {
                squares[k][j].candidates.insert(candidate);
            }
            
            /* add to row */
            if (!squares[i][k].set && checkCandidate(candidate, i, k)) {
                squares[i][k].candidates.insert(candidate);
            }
        }

        /* add to square */
        int i_square = i - i % 3;
        int j_square = j - j % 3;

        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                if (!squares[i_square + x][j_square + y].set && checkCandidate(candidate, i_square + x, j_square + y)) {
                    squares[i_square + x][j_square + y].candidates.insert(candidate);
                }
            }
        }
    }

    /* check if can replace candidate in square */
    bool checkCandidate(int candidate, int i, int j) {
        for (int k = 0; k < 9; k++) {
            /* check columns */
            if (k != i && squares[k][j].set && squares[k][j].val == candidate) return false;
            
            /* check rows */
            if (k != j && squares[i][k].set && squares[i][k].val == candidate) return false;
        }

        /* check surrounding square */
        int i_square = i - i % 3;
        int j_square = j - j % 3;

        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                if (!(i_square + x == i && j_square + y == j) && squares[i_square + x][j_square + y].set && squares[i_square + x][j_square + y].val == candidate) return false;
            }
        }

        return true;
    }

    bool setCandidate(int candidate, std::vector<std::set<std::pair<int,int>>>& pq, int i, int j) {
        squares[i][j].val = candidate;
        squares[i][j].set = true;
        freeCells--;
        return (removeCandidates(candidate, pq, i, j));
    }

    void unsetCandidate(int candidate, std::vector<std::set<std::pair<int,int>>>& pq, int i, int j) {
        squares[i][j].set = false;
        addCandidates(candidate, pq, i, j);
        freeCells++;
    }
};

#endif