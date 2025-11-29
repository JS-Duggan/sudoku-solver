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

void solve(Board& b, bool verbose) {
    /* completion check */
    if (b.freeCells == 0) return;

    std::pair<int, int> next;
    int leastCandidates = 10;

    /* find square with least candidates */
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            /* print statements to see how candidates are reduced and selected */
            if (verbose) {
                std::cout << i << ", " << j << ": ";
                printCandidates(b.squares[i][j]);
            }
            if (!b.squares[i][j].set && !b.squares.empty() && b.squares[i][j].candidates.size() < leastCandidates) {
                next = {i, j};
                leastCandidates = b.squares[i][j].candidates.size();
            }
        }
    }
    if (leastCandidates == 10) return;

    /* branch */
    Square* s = &b.squares[next.first][next.second];
    for(const int candidate : s->candidates) {
        if (verbose) {
            std::cout << "check candidate " << candidate << " for square " << next.first << ", " << next.second << std::endl;
        }

        /* for each candidate, attempt to set. If this results in another unset square having 0 candidates, try next*/
        if (b.setCandidate(candidate, next.first, next.second)) {
            /* all squares have potential candidates, go to next state */
            solve(b, verbose);
            if (b.freeCells == 0)
                return;
        }
        /* remove last set candidate, as wasn't solution */
        b.unsetCandidate(candidate, next.first, next.second);
    }
}

int main() {
    Board b;
    b.readInput();
    bool verbose;
    std::cout << "Print solve logs? (1/0): ";
    std::cin >> verbose;
    solve(b, verbose);
    b.printBoard();
}