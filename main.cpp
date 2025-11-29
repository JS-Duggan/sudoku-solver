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

void setPQ(Board& b, std::vector<std::set<std::pair<int,int>>>& pq) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            Square s = b.squares[i][j];
            if (!s.set && !s.candidates.empty())
                pq[s.candidates.size()].insert({i, j});
        }
    }
}

void solveCool(Board& b, std::vector<std::set<std::pair<int,int>>>& pq, bool verbose) {
    /* create copy for recursion */
    auto pq2 = pq;
    for (const auto& q : pq) {
        for (const auto& coords : q) {
            auto candidates = b.squares[coords.first][coords.second].candidates;
            for (const auto& candidate : candidates) {
                if (b.squares[coords.first][coords.second].set) continue;
                std::cout << "check candidate " << candidate << " for square " << coords.first << ", " << coords.second << std::endl;
                if (b.setCandidate(candidate, pq2, coords.first, coords.second)) {
                    solveCool(b, pq2, verbose);
                    if (b.freeCells == 0)
                        return;
                }
                b.unsetCandidate(candidate, pq2, coords.first, coords.second);
            }
        }
    }
}

int main() {
    Board b;
    bool verbose = false;
    // std::cout << "Print solve logs? (1/0): ";
    // std::cin >> verbose;
    b.readInput();
    std::vector<std::set<std::pair<int,int>>> pq(10);
    setPQ(b, pq);
    solveCool(b, pq, verbose);
    b.printBoard();
}