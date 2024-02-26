/*---------------------------------------------------------------------------*/
#ifndef MATCHING_MCTSAGENT_H
#define MATCHING_MCTSAGENT_H
/*---------------------------------------------------------------------------*/
#include <memory>
/*---------------------------------------------------------------------------*/
#include "mcts/IState.h"
#include "mcts/IAction.h"
#include "mcts/IRewardFunction.h"
#include "mcts/MCTSTree.h"
/*---------------------------------------------------------------------------*/
class MCTSAgent {
public:

    /**@brief Constructor
     *
     * @param ARewardFunction reward function to evaluate a state
     * @param AMaxIterations  max number of iterations
     * @param AMaxSeconds     max number seconds for the process
     * @param AMaxSimulationDepth max depth during the simulation stage
     */
    MCTSAgent(const IRewardFunction* ARewardFunction,
              const int AMaxIterations=100000,
              const int AMaxSeconds=600,
              const int AMaxSimulationDepth=100);
    /**@brief default destructor
     */
    virtual ~MCTSAgent();
    /**@brief Launch the algorithm
     *
     * @param ARootState the state we start from to build the MCSTree
     */
    void run(std::shared_ptr<IState> ARootState);

    /**@brief Compute the best solution by traversing the tree from its root to a leaf. We consider
     * here the best solution as being the most visited node at each level.
     *
     * @return the "best" solution
     */
    std::shared_ptr<IState> get_best_solution();
    /**@brief provides the number of iterations done by the algorithm
     */
    int get_nb_iterations() const {return m_nb_iterations;}
    /**@brief provides the number of seconds used to run the algorithm
     */
    double get_nb_seconds() const {return m_nb_seconds;}

private:
    /**@brief Among all the possible action generated from @p AState, pick one randomly
    * @param[in] AState stage we generate an action from
    * @return the generated action
    */
    std::shared_ptr<IAction> get_random_action(std::shared_ptr<IState> AState) const;
private:

    /**@brief Selection induces a decision policy, known as the tree policy, to navigate
     * through the existing decision tree, attempting to strike a balance between
     * exploration of unknown decision paths and exploitation of known, promising decision paths.
     * @param[in] ANode the node we start the selection from
     * @return the selected node
     */
    MCTSTree* select(MCTSTree* ANode);
    /**@brief Simulation stage. This process returns an expected reward that is computed using a random
     * strategy to compute next stages.
     *
     * @param[in] ANode the node we simulate from
     * @return the reward obtained by the simulation process
     */
    double simulate(MCTSTree* ANode);
    /**@brief Creates a new child for @p ANode by applying an untried actions. If there
     *
     * @param[in] ANode
     * @return
     */
    MCTSTree* expand(MCTSTree* ANode);
    void back_propagate(MCTSTree* ANode, double AReward);
private:
    MCTSTree* m_tree;
    const IRewardFunction* m_reward_function;
    const int m_max_iterations;
    const int m_max_seconds;
    int m_nb_iterations;
    double m_nb_seconds;
    int m_simulation_depth;
};




/*---------------------------------------------------------------------------*/
#endif //MATCHING_MCTSAGENT_H
/*---------------------------------------------------------------------------*/
