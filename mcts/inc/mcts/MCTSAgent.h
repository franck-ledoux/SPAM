/*---------------------------------------------------------------------------*/
#ifndef MATCHING_MCTSAGENT_H
#define MATCHING_MCTSAGENT_H
/*---------------------------------------------------------------------------*/
#include "mcts/IState.h"
#include "mcts/IAction.h"
#include "mcts/IRewardFunction.h"
#include "mcts/MCTSTree.h"
/*---------------------------------------------------------------------------*/
class MCTSAgent {
public:

    MCTSAgent(const IRewardFunction* ARewardFunction,
              const int AMaxIterations=1000000, const int AMaxSeconds=600);
    virtual ~MCTSAgent();
    void execute(IState* ARootState);
    const IState* get_best_solution();
    int get_nb_iterations() const {return m_nb_iterations;}
    int get_nb_seconds() const {return m_nb_seconds;}
private:

    /** Selection induces a decision policy, known as the tree policy, to navigate
     * through the existing decision tree, attempting to strike a balance between
     * exploration of unknown decision paths and exploitation of known, promising decision paths.
     * @param[in] ANode the node we start the selectio from
     * @return the selected node and the reward associated to this node
     */
    MCTSTree* select(MCTSTree* ANode);
    double simulate(MCTSTree* ANode);
    MCTSTree* expand(MCTSTree* ANode);
    void back_propagate(MCTSTree* ANode, double AReward);
private:
    MCTSTree* m_tree;
    const IRewardFunction* m_reward_function;
    const int m_max_iterations;
    const int m_max_seconds;
    int m_nb_iterations;
    int m_nb_seconds;
};




/*---------------------------------------------------------------------------*/
#endif //MATCHING_MCTSAGENT_H
/*---------------------------------------------------------------------------*/
