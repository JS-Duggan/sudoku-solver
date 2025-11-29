#include <utility>
#include <iostream>
#include "board.cpp"

void printCandidates(Square& s) {
    std::cout << "{";
    for (const int candidate : s.candidates) {
        std::cout << " " << candidate;
    }
    std::cout << " }\n";
}

void solveCool(Board& b, std::vector<std::set<std::pair<int,int>>>& pq, bool verbose) {
    for (const auto& q : pq) {
        for (const auto& coords : q) {
            for (const auto& candidate : b.squares[coords.first][coords.second].candidates) {
                if (b.setCandidate(candidate, pq, coords.first, coords.second)) {
                    solveCool(b, pq, verbose);
                    if (b.freeCells == 0)
                        return;
                }
                b.unsetCandidate(candidate, pq, coords.first, coords.second);
            }
        }
    }
}

int main() {
    Board b;
    std::vector<std::set<std::pair<int,int>>> pq(9);
    b.readInput(pq);
    bool verbose;
    std::cout << "Print solve logs? (1/0): ";
    std::cin >> verbose;
    solveCool(b, pq, verbose);
    b.printBoard();
}