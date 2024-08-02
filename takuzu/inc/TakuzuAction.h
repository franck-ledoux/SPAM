/*---------------------------------------------------------------------------*/
#ifndef SPAM_TAKUZU_ACTION_H
#define SPAM_TAKUZU_ACTION_H
/*---------------------------------------------------------------------------*/
#include "mcts/IAction.h"
#include <iostream>
#include <memory>
/*---------------------------------------------------------------------------*/
class TakuzuAction : public IAction {
public:
    const int i;
    const int j;
    const char value;

    TakuzuAction(const int AI, const int AJ, const char AVal);


    /**@brief Computes the state reach from the current one when applying @p AAction
     * @param AAction the action to apply
     * @return the state that is built from this one when applying @p AAction
     */
    std::shared_ptr<IState> apply_on(std::shared_ptr<IState>  AState) const override;

    bool operator==(const IAction& other) const override;

    friend std::ostream& operator<<(std::ostream& os, const TakuzuAction& TA);

};
/*---------------------------------------------------------------------------*/
#endif //SPAM_TAKUZU_ACTION_H
/*---------------------------------------------------------------------------*/
