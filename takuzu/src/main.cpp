/*---------------------------------------------------------------------------*/
#include <iostream>
#include "../inc/TakuzuRewardFunction.h"
#include "../inc/TakuzuState.h"
#include "mcts/MCTSAgent.h"
/*---------------------------------------------------------------------------*/
int main() {
    auto s = std::make_shared<TakuzuState>();
    s->board[0][0]='0';
    s->board[0][2]='1';
    s->board[0][3]='1';
    s->board[1][2]='0';
    s->board[2][1]='0';
    s->board[3][0]='0';
    s->board[3][2]='1';
    std::cout<<"Initial grid:"<<std::endl<<*s<<std::endl;

    TakuzuRewardFunction reward_function;
    MCTSAgent agent(&reward_function,100);//1000000);
    agent.activate_debug_mode("takuzu", MCTSAgent::OUT_ITERATION,1000);
    agent.run(s);
    std::cout<<"Nb runs: "<<agent.get_nb_iterations()-1,
    std::cout<<", timing: "<<agent.get_nb_seconds()<<" s."<<std::endl;
    std::cout<<"Best solution:"<<std::endl;
    std::cout<<*std::dynamic_pointer_cast<TakuzuState>(agent.get_best_solution())<<std::endl;
}