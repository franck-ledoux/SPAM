/*---------------------------------------------------------------------------*/
#include "mcts/MCTSTree.h"
#include <cmath>
#include <iostream>
#include <cfloat>
#include <limits>
/*---------------------------------------------------------------------------*/
MCTSTree::
MCTSTree(const IState *AState, MCTSTree *AParent, IAction *AAction)
: m_state(AState), m_parent(AParent), m_action(AAction),
cumulative_reward(0), nb_simulations(0), m_untried_actions(m_state->get_actions_to_try())
{}
/*---------------------------------------------------------------------------*/
MCTSTree::~MCTSTree() {
    if(m_state!= nullptr)
        delete m_state;

    if(m_action!= nullptr)
        delete m_action;

    for(auto &c : m_children){
        if(c!= nullptr)
            delete c;
    }
    for(auto &a : m_untried_actions){
        if(a!= nullptr)
            delete a;
    }
}
/*---------------------------------------------------------------------------*/
const IState* MCTSTree::get_state() const {
    return m_state;
}
/*---------------------------------------------------------------------------*/
IAction* MCTSTree::get_action() const {
    return m_action;
}
/*---------------------------------------------------------------------------*/
MCTSTree* MCTSTree::get_parent() const {
    return  m_parent;
}
/*---------------------------------------------------------------------------*/
bool MCTSTree::is_terminal() const {
    return m_state->is_terminal();
}
/*---------------------------------------------------------------------------*/
bool MCTSTree::is_fully_expanded() const {
    return  m_untried_actions.empty();
}
/*---------------------------------------------------------------------------*/
MCTSTree* MCTSTree::get_most_visited_child() const {
    if(m_children.empty())
        return nullptr;

    MCTSTree* most_visited = m_children[0];
    for(auto c:m_children){
        if (c->nb_simulations>most_visited->nb_simulations){
            most_visited=c;
        }
    }
    std::cout<<"Most visited: "<<most_visited->nb_simulations<<std::endl;
    return  most_visited;
}
/*---------------------------------------------------------------------------*/
void MCTSTree::add_child(MCTSTree* AChild) {
    m_children.push_back(AChild);
    //and we remove the action that lead to create this child from the list of
    //actions
    auto a = AChild->get_action();
    int a_index = -1;
    for(auto i=0; i<m_untried_actions.size() && a_index==-1;i++){
        if(m_untried_actions[i]==a)
            a_index = i;
    }
    //we remove the action now
    if(a_index!=m_untried_actions.size()-1){
        m_untried_actions[a_index]= m_untried_actions.back();

    }
    m_untried_actions.pop_back();
}

/*---------------------------------------------------------------------------*/
void MCTSTree::remove_children() {
    for(auto c:m_children){
        delete c;
    }
}
/*---------------------------------------------------------------------------*/
MCTSTree* MCTSTree::get_child(const IAction* AAction) const {
    for(auto c:m_children) {
        if (c->get_action() == AAction)
            return c;
    }
    return nullptr;
}
/*---------------------------------------------------------------------------*/
MCTSTree*  MCTSTree::expand()  {
    if (is_terminal())
        return this;
    auto action = random_action();
    if(action== nullptr)
        throw std::exception();
    auto next_state = m_state->apply(action);
    auto child =  new MCTSTree(next_state);
    add_child(child);
    return child;
}
/*---------------------------------------------------------------------------*/
const IAction* MCTSTree::select_action_UCT(double AC) const {
    // sanity check
    //TODO it should be fully expanded in practice
 //   if(!node->is_fully_expanded()) return NULL;

    if (m_children.empty())
        throw std::exception();

    if (m_children.size() == 1)
        return m_children[0]->get_action();

    float best_utc_score = -std::numeric_limits<float>::max();
    MCTSTree* best_node = NULL;

    // iterate all immediate children and find best UTC score
    int num_children = m_children.size();
    for(auto i = 0; i < num_children; i++) {
        auto child = m_children[i];
        float uct_exploitation = (float)child->cumulative_reward / (child->nb_simulations + FLT_EPSILON);
        float uct_exploration = sqrt( log((float)this->nb_simulations + 1) / (child->nb_simulations + FLT_EPSILON) );
        float uct_score = uct_exploitation + AC * uct_exploration;

        if(uct_score > best_utc_score) {
            best_utc_score = uct_score;
            best_node = child;
        }
    }

    return best_node->get_action();

}
/*---------------------------------------------------------------------------*/
IAction* MCTSTree::random_action() const {
    /** selects an action among the untried ones */
    if (m_untried_actions.empty())
        return nullptr;

    //randomly pick an action
    return m_untried_actions[std::rand()%m_untried_actions.size()];
}