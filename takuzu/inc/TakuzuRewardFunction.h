/*---------------------------------------------------------------------------*/
#ifndef SPAM_TAKUZU_REWARD_FUNC_H
#define SPAM_TAKUZU_REWARD_FUNC_H
/*---------------------------------------------------------------------------*/
#include "mcts/IRewardFunction.h"
#include <iostream>
#include <memory>
/*---------------------------------------------------------------------------*/
struct TakuzuRewardFunction: public IRewardFunction{


    double evaluate(std::shared_ptr<IState> AState) const override;

};
/*---------------------------------------------------------------------------*/
#endif //SPAM_TAKUZU_REWARD_FUNC_H
/*---------------------------------------------------------------------------*/
