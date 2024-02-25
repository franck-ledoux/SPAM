# SPAM
SPAM yields for **Single PlAyer Monte carlo tree search**. 
It is an implementation of Monte Carlo Tree Search that focuses on single-player games.

## MCTS Implementation
We provide a single-player MCTS implementation in the directory [mcts](/mcts).
Running this MCTS on your problem requires to implement three interfaces, which are:
- [IState](mcts/inc/mcts/IState.h) gathers the requirement your state must fulfill;
- [IAcation](mcts/inc/mcts/IAction.h) indicates how to compare actions;
- [IRewardFunction](mcts/inc/mcts/IRewardFunction.h) contains the reward evaluation of a given state.

The memory management of the MCTS is based on smart (std::shared_ptr) and raw pointers. Memory check is regularly
performed and there is no memory leak in the current implementation. In order to avoid memory issues as much
as possible, previous interfaces only use smart pointers.

An example of problem solving using this MCTS implementation is given in [takuzu](/takuzu). The takuzu is
a Sudoku-like problem that is played by a single player. 

## MCTS explained

There exist many ways to implement a MCTS. The version proposed here is mainly inspired by https://gibberblot.github.io/rl-notes/single-agent/mcts.html.

## Further readings
- A research paper on the single-player problem: https://dke.maastrichtuniversity.nl/m.winands/documents/CGSameGame.pdf.
- A recent review (2022) on the Monte Carlo Tree Search technique: https://arxiv.org/abs/2103.04931.
