# Sudoku Solver

## Description

A brute force approach to solving sudo puzzles using backtracking. The approach taken selects the next square to try based on the most constrained square. Pruning is done on a look-ahead basis, where a square that has not been filled and has no remaining possible values causes the branch to be pruned. 