/*---------------------------------------------------------------------------*/
#include <iostream>
#include "../inc/TakuzuAction.h"
#include "../inc/TakuzuState.h"

/*---------------------------------------------------------------------------*/
std::shared_ptr<IState> TakuzuAction::apply_on(const std::shared_ptr<IState> AState) const {

    auto prev_state = std::dynamic_pointer_cast<TakuzuState>(AState);
    auto next_state = std::make_shared<TakuzuState>(*prev_state);

    next_state->board[i][j]=value;
    return next_state;
}
/*---------------------------------------------------------------------------*/
TakuzuAction::TakuzuAction(const int AI, const int AJ, const char AVal)
        :i(AI),j(AJ),value(AVal){;};
/*---------------------------------------------------------------------------*/
bool TakuzuAction::operator==(const IAction &other) const {
    const auto &o = (const TakuzuAction &) other;
    return i == o.i && j == o.j && value == o.value;
}
/*---------------------------------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const TakuzuAction& TA){
    os<<"("<<TA.i<<"-"<<TA.j<<":"<<TA.value<<")";
    return os;
}
/*---------------------------------------------------------------------------*/
