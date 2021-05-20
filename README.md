# Tetris Solver

## Path Finding Complexity
Tetris can be formulated as a graph search problem. The nodes are the possible states of a tetris board. The board is a 20 x 10 grid, and each cell can be occupied or not. So a loose upper bound is 2^60 ~ 1e18 states, though many of these are impossible. The paths are sequences of actions to maneuver a piece into place. A piece can be rotated left or right, as well as shifted left or right. Assuming one action per drop frame, an upper bound is 4^20 ~ 1e12 paths per piece, though many of these actions are illegal. Finding the optimal path has been shown to be NP complete. These are difficult problems!

## Efficient Backend
Finding the best end states is an open problem. Genetic algorithms have been shown to provide super human evaluation functions. However, training time is directly dependent on the performance of the game engine. The main goal is to provide an efficient backend to optimize game execution and board state cacheing. A lightweight gui using SFML2 will display real time performance of a trained agent.

## Bitboard
Bitboards are the most efficient way to represent board states. A tetris board is equivalent to a 200-bit integer. Boost Multiprecision Library provides 256-bit integers. The extra bits are used for piece queueing and borders. Besides efficient cacheing, bit manipulations allow for parallelized operations. So counting line clears is extremely efficient. A few more tricks allow for efficient feature calculations for ML agents. These details are found in bitboard, board, and features source files.
