/*---------------------------------------------------------------------------*/
#ifndef MATCHING_MCTSTREE_H
#define MATCHING_MCTSTREE_H
/*---------------------------------------------------------------------------*/
#include "mcts/IState.h"
#include "mcts/IAction.h"
#include "mcts/IRewardFunction.h"
#include <memory>
/*---------------------------------------------------------------------------*/
class MCTSTree{
public:
    MCTSTree(const IState* AState, MCTSTree* AParent = nullptr, IAction* AAction = nullptr);

    /**@brief Default destructor
     */
    ~MCTSTree();

    /**@brief Provides the state associated to the root node
     * @return the current root state
     */
    const IState* get_state() const;

    /**@brief Give access to the parent node
     * @return Returns the parent node. Returns nullptr for the root node
     */
   MCTSTree* get_parent() const;

    /**@brief Provides the action that allows to create this node from its
     *        parent
     * @return an action, which can be null for the root
     */
    IAction* get_action() const;

    /** Return the child that can be reached applying the action @p AAction.
     * It returns the node if it exists, but do not create it otherwise.
     * @param[in] AAction
     * @return the expected node, or nullptr if it doesn't exist
     */
    MCTSTree* get_child(const int AI) const;

    MCTSTree* get_most_visited_child() const;

    MCTSTree*  add_child_with_action( IAction* new_action);

    MCTSTree*  expand();
    /** @return true if it doesn't remain actions to perform for generating child,
     * false otherwise
     * All children have been expanded and simulated
     */
    bool is_fully_expanded() const;
    /**@brief a node is terminal when the associated state is said "win" or "lost".
     * In other word, the game is over
     * @return true if the game is over, false otherwise.
     */
    bool is_terminal() const;

    bool has_children() const;
    /**@brief Among all the children, provide the action that reach it
     *        based on the exploration/exploitation principle (UCT criterion here)
       * @return the selected action
       */
    MCTSTree*  get_best_uct_child(double AC=1.41) const;


    /** total reward of the current node */
    double cumulative_reward;
    /** number of times the node has been explored */
    int number_visits;

private:
    /** current state **/
    const IState* m_state;
    /** parent node that is shared with all the siblings**/
    MCTSTree*  m_parent;
    /** action that generates this node from the parent **/
    IAction* m_action;
    /** children nodes, that are potentially empty. When a children node
     * is generated, it means that an action is remove from the m_untried_actions
     * collection **/
    std::vector<MCTSTree*> m_children;

    std::vector<IAction*> m_actions;
};
/*---------------------------------------------------------------------------*/
#endif //MATCHING_MCTSTREE_H
/*---------------------------------------------------------------------------*/
