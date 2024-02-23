/*---------------------------------------------------------------------------*/
#ifndef MATCHING_IREWARDFUNCTION_H
#define MATCHING_IREWARDFUNCTION_H
/*---------------------------------------------------------------------------*/
#include <mcts/IAction.h>
#include <mcts/IState.h>
/*---------------------------------------------------------------------------*/
struct IRewardFunction {
    virtual ~IRewardFunction() = default;

    /**@brief this function must give the expected reward when you goes from
     * state @p AStateFrom to state @p AStateTo using action @p AAction
     *
     * @param AStateFrom origin state
     * @param AAction    transition action
     * @param AStateTo   destination state
     * @return a double value comprised in [0,1]
     */
    virtual double compute(const IState* AStateFrom,
                           const IAction* AAction,
                           const IState* AStateTo) const = 0;
};
/*---------------------------------------------------------------------------*/
#endif //MATCHING_IREWARDFUNCTION_H
/*---------------------------------------------------------------------------*/
