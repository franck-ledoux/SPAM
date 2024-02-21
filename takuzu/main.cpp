/*---------------------------------------------------------------------------*/
#include <iostream>
#include "Takuzu.h"
#include "mcts/MCTSAgent.h"
/*---------------------------------------------------------------------------*/
int main() {
    std::shared_ptr<TakuzuState> s = std::make_shared<TakuzuState>();
    s->board[0][0]='0';
    s->board[0][2]='1';
    s->board[0][3]='1';
    s->board[1][2]='0';
    s->board[2][1]='0';
    s->board[3][0]='0';
    s->board[3][2]='1';
    std::cout<<"Grid:"<<std::endl<<*s<<std::endl;
    auto actions = s->get_actions_to_try();

    auto reward_function = std::make_shared<TakuzuRewardFunction>();
    MCTSAgent agent(reward_function);
    agent.execute(s);
    std::cout<<"Nb runs: "<<agent.get_nb_iterations()<<std::endl;
    std::cout<<"Timing : "<<agent.get_nb_seconds()<<" s."<<std::endl;
    std::cout<<"Best solution:"<<std::endl;
    std::cout<<*std::dynamic_pointer_cast<TakuzuState>(agent.get_best_solution())<<std::endl;
}