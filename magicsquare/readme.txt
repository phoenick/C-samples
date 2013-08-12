Nikolaos Bikos

magicsquare

This program is designed to solve "magicsquare" puzzles of any size (up to a limit).

Magicsquare rules: 
-We begin with an empty matrix n x n
-Number 1 goes in top left corner
-For every number k from 1 to n^2 - 1, numbers k and k+1 must have been placed in the same line or in
the same row, but having 2 empty spots between them, or they can be in the same diagonal with one
empty spot between them.
-The goal of the game is to fill the matrix with numbers using these rules so as to leave no empty spot


Algorithm
The program tries to solve the puzzle by making random choices at start and then if it doesn't reach a 
solution, then it backtracks to the most recent choice and makes another one from the available choice.
Basically, it is an implementation of a Depth-First search algorithm, but examined in a context where 
backtracking is the main concept.