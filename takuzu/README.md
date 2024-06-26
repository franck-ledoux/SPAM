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

In order to solve it using our MCTS implementation, we run the following set of C++ lines that occur
in file [main.cpp](mcts/inc/mcts/IState.h):

```cpp
auto s = std::make_shared<TakuzuState>();
TakuzuRewardFunction reward_function;

MCTSAgent agent(&reward_function, nb_mcts_iter);

MCTSLoop loop(agent, s, MCTSLoop::BEST_CHILD, nb_loop_iter, true);
loop.run();
```
In order to explain how our implemenation is working, let us give a few insights about those code lines:
- The two first lines corresponds to initialize the implementation of the `IState` and `IRewarFunction` interfaces
for the current example of Takuzu.
- The third line initializes the agent that will progressively build and travers the MCTS tree. In particular, we give
him the max number of iteration he will do in the classical MCTS loop process.
- At the fourth line, an `MCTSLoop` object is created and it will the one that run the whole procedure 
(see [here](../README.md)). 