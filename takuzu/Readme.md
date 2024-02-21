# Game Presentation
The *tukazu* game is a simplified version of *Sudoku*. 
Considering a grid of size NxN, the goal is to fill each line and column of the grid
with 0 and 1, such that:
1. Each line, i.e. column, contains the same number of 0 and 1. So a grid of size 6x6 will contain three 0 and three 1 in each line and column.
2. Not more than two consecutive 0 and 1.
3. Two lines or two columns cannot be identical.

In this example, we consider the two first rules and we start from a 4x4 grid that we initialize as follows:

| 0 |   | 1 | 1 |
|---|---|---|---|
|   |   | 0 |   |
|   | 0 |   |   |
| 0 |   | 1 |   |
