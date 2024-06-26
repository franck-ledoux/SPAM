/*---------------------------------------------------------------------------*/
#include <iostream>
#include "../inc/TakuzuRewardFunction.h"
#include "../inc/TakuzuState.h"
#include "mcts/MCTSAgent.h"
#include "mcts/MCTSLoop.h"
/*---------------------------------------------------------------------------*/
int main() {
    auto s = std::make_shared<TakuzuState>();
    s->board[0][0] = '0';
    s->board[0][2] = '1';
    s->board[0][3] = '1';
    s->board[1][2] = '0';
    s->board[2][1] = '0';
    s->board[3][0] = '0';
    s->board[3][2] = '1';
    std::cout << "Initial grid:" << std::endl << *s << std::endl;

    auto nb_mcts_iter = 1000;
    auto nb_loop_iter = 100;
    bool get_best_solution = false;
    TakuzuRewardFunction reward_function;
    MCTSAgent agent(&reward_function, nb_mcts_iter);
    agent.activate_debug_mode("takuzu", MCTSAgent::OUT_END_ONLY, 1000);

    MCTSLoop loop(agent, s, MCTSLoop::BEST_CHILD, nb_loop_iter, true);
    loop.run();
    std::cout << "Best solution:" << std::endl;
    std::cout <<  *std::dynamic_pointer_cast<TakuzuState>(agent.get_best_solution()) << std::endl;
    std::cout << "With total number of iterations: " << loop.get_nb_iterations() << std::endl;

}
