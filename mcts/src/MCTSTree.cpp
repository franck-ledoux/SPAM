/*---------------------------------------------------------------------------*/
#include "mcts/MCTSTree.h"
/*---------------------------------------------------------------------------*/
MCTSTree::MCTSTree(const std::shared_ptr<IState> AState,
                   const std::shared_ptr<MCTSTree> AParent,
                   const std::shared_ptr<IAction> AAction)
        : m_state(AState), m_parent(AParent), m_action(AAction),
        cumulative_reward(0), nb_simulations(0)
{
    //When we create a node, we compute the possible actions that can be
    // performed from it.
    m_untried_actions = m_state->get_actions_to_try();
}

/*---------------------------------------------------------------------------*/
MCTSTree::MCTSTree(const std::shared_ptr<MCTSTree> ATree)
        : m_state(ATree->get_state()),
        m_parent(ATree->get_parent()),
        m_action(ATree->get_action()),
        cumulative_reward(ATree->cumulative_reward),
        nb_simulations(ATree->nb_simulations),
        m_untried_actions(ATree->m_untried_actions),
        m_children(ATree->m_children)
{}
/*---------------------------------------------------------------------------*/
MCTSTree::~MCTSTree() {}
/*---------------------------------------------------------------------------*/
const std::shared_ptr<IState> MCTSTree::get_state() const {
    return m_state;
}
/*---------------------------------------------------------------------------*/
const std::shared_ptr<IAction> MCTSTree::get_action() const {
    return m_action;
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
std::shared_ptr<MCTSTree> MCTSTree::get_most_visited_child() const {
    if(m_children.empty())
        return nullptr;

    std::shared_ptr<MCTSTree> most_visited = m_children[0];
    for(auto c:m_children){
        if (c->nb_simulations>most_visited->nb_simulations){
            most_visited=c;
        }
    }
    return  most_visited;
}
/*---------------------------------------------------------------------------*/
void MCTSTree::add_child(const std::shared_ptr<MCTSTree> AChild) {
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
std::shared_ptr<MCTSTree> MCTSTree::
get_child(const std::shared_ptr<IAction> AAction) {
    for(auto c:m_children) {
        if (c->get_action() == AAction)
            return c;
    }
    return nullptr;
}
/*---------------------------------------------------------------------------*/
void MCTSTree::expand_children()  {
    auto action = random_action();
    if(action!= nullptr) {
        auto next_state = m_state->apply(action);
        add_child(std::make_shared<MCTSTree>(next_state, std::make_shared<MCTSTree>(*this), action));
    }
}
/*---------------------------------------------------------------------------*/
const std::shared_ptr<MCTSTree> MCTSTree::get_parent() const {
    return  m_parent;
}
/*---------------------------------------------------------------------------*/
std::shared_ptr<IAction> MCTSTree::select_action(double AC) const {
    if (m_children.empty())
        return nullptr;

    if (m_children.size() == 1)
        return m_children[0]->get_action();

    double uct=0, max = -1;
    std::shared_ptr<MCTSTree> argmax;// = std::make_shared<MCTSTree>(nullptr);
    for (auto  child: m_children) {
        double winrate = child->cumulative_reward / ((double) child->nb_simulations+1);
        if (AC> 0) {
            uct = winrate +
                  AC * sqrt(log((double) this->nb_simulations) / ((double) child->nb_simulations+1));
        }
        else {
            uct = winrate;
        }
        if (uct > max) {
            max = uct;
            argmax = child;
        }
    }
    return argmax->get_action();
}
/*---------------------------------------------------------------------------*/
std::shared_ptr<IAction> MCTSTree::random_action() const {
    /** selects an action among the untried ones */
    if (m_untried_actions.empty())
        return nullptr;

    //randomly pick an action
    return m_untried_actions[std::rand()%m_untried_actions.size()];
}