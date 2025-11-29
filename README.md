# Sudoku Solver

## Description

A brute force approach to solving sudo puzzles using backtracking. The approach taken selects the next square to try based on the most constrained square. Pruning is done on a look-ahead basis, where a square that has not been filled and has no remaining possible values causes the branch to be pruned. 

## Usage

When the program is run, it will expect an input string. Some examples are given in testStrings.txt. Ths 0's represent empty squares. The program will then 
print the solved puzzle.