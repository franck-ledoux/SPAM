/*---------------------------------------------------------------------------*/
#include "mcts/MCTSAgent.h"
#include <chrono>
#include <iostream>
/*---------------------------------------------------------------------------*/
MCTSAgent::MCTSAgent(const std::shared_ptr<IRewardFunction> ARewardFunction,
                     int AMaxIterations, int AMaxSeconds)
: m_tree(nullptr),
m_reward_function(ARewardFunction),
m_max_iterations(AMaxIterations),
m_max_seconds(AMaxSeconds)
{}
/*---------------------------------------------------------------------------*/
MCTSAgent::~MCTSAgent() {}
/*---------------------------------------------------------------------------*/
void MCTSAgent::execute(std::shared_ptr<IState> ARootState) {
    //Build the initial tree
   m_tree  = make_tree(ARootState);

    int i=0;
    auto time0 = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::ratio<1>> elapsed= std::chrono::steady_clock::now()-time0;

    while (i<=m_max_iterations && elapsed.count() <= m_max_seconds){

        // we explore/exploit the existing tree to find a node to work on
        auto [tree_i,reward_i] = selection_policy(m_tree);

        expand_policy(tree_i);
        // we simulate an execution from the selected node
        auto reward = simulation_policy(tree_i);

        //we backpropagate the obtained reward in the tree
        back_propagate(tree_i,reward);
        //increase loop counters
        i++;
        elapsed= std::chrono::steady_clock::now()-time0;
    }
    m_nb_iterations=i;
    m_nb_seconds =elapsed.count();
}
/*---------------------------------------------------------------------------*/
void MCTSAgent::expand_policy(std::shared_ptr<MCTSTree> ANode) {
    //auto prev_node = ANode->get_parent();
    ANode->expand_children();
}
/*---------------------------------------------------------------------------*/
std::shared_ptr<MCTSTree> MCTSAgent::make_tree(const std::shared_ptr<IState> AState,
                                               const std::shared_ptr<MCTSTree> AParent,
                                               const std::shared_ptr<IAction> AAction){
    return std::make_shared<MCTSTree>(AState,AParent,AAction);
}
/*---------------------------------------------------------------------------*/
std::shared_ptr<IState> MCTSAgent::get_best_solution() {
    auto current_node = m_tree;
    while (!current_node->is_terminal()){
        current_node=current_node->get_most_visited_child();
    }
    return current_node->get_state();
}
/*---------------------------------------------------------------------------*/
double MCTSAgent::simulation_policy(std::shared_ptr<MCTSTree> ANode) {
    auto current_node = ANode;
    auto current_state = current_node->get_state();
    double reward = 0;
    while (!current_state->is_terminal()) {
        auto action = current_node->random_action();
        auto next_state = current_state->apply(action);
        reward += m_reward_function->compute(current_state,action,next_state);
        //we are in simulation mode, so the next node does not exist
        auto child_node = make_tree(next_state,
                                        current_node,
                                        action);
        current_node->add_child(child_node);
        current_node = child_node;
        current_state = current_node->get_state();
    }
    return reward;
}
/*---------------------------------------------------------------------------*/
std::pair<std::shared_ptr<MCTSTree>, double>
MCTSAgent::selection_policy(std::shared_ptr<MCTSTree> ANode) {
    double reward = 0;
    auto current_node = ANode;
    auto current_state = current_node->get_state();

    while (!current_state->is_terminal()){
        auto action = current_node->select_action();
        if(action== nullptr){
            //no child, we need to perform simulation
            return std::make_pair(current_node,reward);
        }
        auto next_node = current_node->get_child(action);

        auto next_state = next_node->get_state();
        reward += m_reward_function->compute(current_state,action,next_state);
      /*  // Is it the first observation of the transition from current_state to
        // next_state ?
        if(next_node== nullptr){
            //first time, we apply this action from this node
            //we create the child node
            auto child_node = make_tree(next_state,
                                        current_node,
                                        action);
            //we add it to the current node
            current_node->add_child(child_node);
            return std::make_pair(child_node,reward);
        }
        */
      //action already done, the child exists
        current_node = next_node;
        current_state = current_node->get_state();
    }
    //We have reached a terminal node here
    return  std::make_pair(current_node,reward);
}
/*---------------------------------------------------------------------------*/
void MCTSAgent::back_propagate(std::shared_ptr<MCTSTree> ANode, double AReward) {
    auto current_node = ANode;
    while(current_node!= nullptr){
        current_node->cumulative_reward+=AReward;
        current_node->nb_simulations+=1;
        current_node = current_node->get_parent();
    }
}

