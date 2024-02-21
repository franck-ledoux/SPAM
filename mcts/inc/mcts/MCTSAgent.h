/*---------------------------------------------------------------------------*/
#ifndef MATCHING_MCTSAGENT_H
#define MATCHING_MCTSAGENT_H
/*---------------------------------------------------------------------------*/
#include <memory>
#include "mcts/IState.h"
#include "mcts/IAction.h"
#include "mcts/IRewardFunction.h"
#include "mcts/MCTSTree.h"
/*---------------------------------------------------------------------------*/
class MCTSAgent {
public:

    MCTSAgent(const std::shared_ptr<IRewardFunction> ARewardFunction,
              const int AMaxIterations=10000, const int AMaxSeconds=600);
    virtual ~MCTSAgent();
    void execute(std::shared_ptr<IState> ARootState);
    std::shared_ptr<IState> get_best_solution();
    int get_nb_iterations() const {return m_nb_iterations;}
    int get_nb_seconds() const {return m_nb_seconds;}
private:
    std::shared_ptr<MCTSTree> make_tree(const std::shared_ptr<IState> AState,
                                        const std::shared_ptr<MCTSTree> AParent= nullptr,
                                        const std::shared_ptr<IAction> AAction= nullptr);

    /** Selection induces a decision policy, known as the tree policy, to navigate
     * through the existing decision tree, attempting to strike a balance between
     * exploration of unknown decision paths and exploitation of known, promising decision paths.
     * @param[in] ANode the node we start the selectio from
     * @return the selected node and the reward associated to this node
     */
    std::pair<std::shared_ptr<MCTSTree>, double> selection_policy(std::shared_ptr<MCTSTree> ANode);
    double simulation_policy(std::shared_ptr<MCTSTree>);
    void expand_policy(std::shared_ptr<MCTSTree> ANode);
    void back_propagate(std::shared_ptr<MCTSTree> ANode, double AReward);
private:
    std::shared_ptr<MCTSTree> m_tree;
    const std::shared_ptr<IRewardFunction> m_reward_function;
    const int m_max_iterations;
    const int m_max_seconds;
    int m_nb_iterations;
    int m_nb_seconds;
};




/*---------------------------------------------------------------------------*/
#endif //MATCHING_MCTSAGENT_H
/*---------------------------------------------------------------------------*/
