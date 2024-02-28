/*---------------------------------------------------------------------------*/
#include "../inc/TakuzuRewardFunction.h"
#include "../inc/TakuzuState.h"
/*---------------------------------------------------------------------------*/
double TakuzuRewardFunction::evaluate(std::shared_ptr<IState> AState) const {
    if(std::dynamic_pointer_cast<TakuzuState>(AState)->win())
        return 1;
    else if(std::dynamic_pointer_cast<TakuzuState>(AState)->lost())
        return -1;
    return 0;
}
