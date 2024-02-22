/*---------------------------------------------------------------------------*/
#ifndef MATCHING_MCTSTREE_H
#define MATCHING_MCTSTREE_H
/*---------------------------------------------------------------------------*/
#include <memory>
#include "mcts/IState.h"
#include "mcts/IAction.h"
#include "mcts/IRewardFunction.h"
/*---------------------------------------------------------------------------*/
class MCTSTree{
public:
    MCTSTree(const std::shared_ptr<IState> AState,
             const std::shared_ptr<MCTSTree> AParent = nullptr,
             const std::shared_ptr<IAction> AAction = nullptr);
    MCTSTree(const std::shared_ptr<MCTSTree> ATree);
    /**@brief Default destructor
     */
    ~MCTSTree();
    /**@brief Provides the state associated to the root node
     * @return the current root state
     */
    const std::shared_ptr<IState> get_state() const;
    /**@brief Give access to the parent node
     * @return Returns the parent node. Returns nullptr for the root node
     */
    const std::shared_ptr<MCTSTree> get_parent() const;

    /**@brief Provides the action that allows to create this node from its
     *        parent
     * @return an action, which can be null for the root
     */
    const std::shared_ptr<IAction> get_action() const;
    /** Return the child that can be reached applying the action @p AAction.
     * It returns the node if it exists, but do not create it otherwise.
     * @param[in] AAction
     * @return the expected node, or nullptr if it doesn't exist
     */
    std::shared_ptr<MCTSTree> get_child(const std::shared_ptr<IAction> AAction);

    std::shared_ptr<MCTSTree> get_most_visited_child() const;

    /**@brief Add a child node to this one. This operation does not check if an
     * existing child already exist for the same action. It also does'nt check that
     * you do not provide a nullptr
     * @param[in] AChild A non null tree
     */
    void add_child(const std::shared_ptr<MCTSTree> AChild);

    std::shared_ptr<MCTSTree>  expand();
    /** @return true if it doesn't remain actions to perform for generating child,
     * false otherwise
     */
    bool is_fully_expanded() const;
    /**@brief a node is terminal when the associated state is said "win" or "lost".
     * In other word, the game is over
     * @return true if the game is over, false otherwise.
     */
    bool is_terminal() const;

    /**@brief Among all the children, provide the action that reach it
     *        based on the exploration/exploitation principle (UCT criterion here)
       * @return the selected action
       */
    std::shared_ptr<IAction> select_action_UCT(double AC=1.41) const;
    /**@brief Among all the possible action to try, provide one to apply randomly
     * @return the selected action
     */
    std::shared_ptr<IAction> random_action() const;


    /** total reward of the current node */
    double cumulative_reward;
    /** number of times the node has been explored */
    int nb_simulations;
private:
    /** current state **/
    const std::shared_ptr<IState> m_state;
    /** parent node that is shared with all the siblings**/
    std::shared_ptr<MCTSTree>  m_parent;
    /** action that generate this node from the parent **/
    const std::shared_ptr<IAction> m_action;
    /** children nodes, that are potentially empty. When a children node
     * is generated, it means that an action is remove from the m_untried_actions
     * collection **/
    std::vector<std::shared_ptr<MCTSTree>> m_children;

    std::vector<std::shared_ptr<IAction> > m_untried_actions;
};
/*---------------------------------------------------------------------------*/
#endif //MATCHING_MCTSTREE_H
/*---------------------------------------------------------------------------*/
