/*---------------------------------------------------------------------------*/
#include <iostream>
#include "Takuzu.h"
/*---------------------------------------------------------------------------*/
TakuzuState::TakuzuState() {
    for (auto i = 0; i < 4; i++) {
        for (auto j = 0; j < 4; j++) {
            board[i][j] = '.';
        }
    }
}
/*---------------------------------------------------------------------------*/
TakuzuState::TakuzuState(const TakuzuState &AState) {
    for (auto i = 0; i < 4; i++) {
        for (auto j = 0; j < 4; j++) {
            board[i][j] = AState.board[i][j];
        }
    }
}
/*---------------------------------------------------------------------------*/
std::vector<std::shared_ptr<IAction> > TakuzuState::get_actions() const
{
    std::vector<std::shared_ptr<IAction> > actions;
    for (auto i = 0; i < 4; i++) {
        for (auto j = 0; j < 4; j++) {
            if(board[i][j]=='.'){
                actions.push_back(std::make_shared<TakuzuAction>(i,j,'0'));
                actions.push_back(std::make_shared<TakuzuAction>(i,j,'1'));
            }
        }
    }
    return actions;
}
/*---------------------------------------------------------------------------*/
const IState* TakuzuState::
apply(const IAction* AAction) const {
    auto next_state = new TakuzuState(*this);
    auto a = dynamic_cast<const TakuzuAction*>(AAction);
    next_state->board[a->i][a->j]=a->value;
    return next_state;
}
/*---------------------------------------------------------------------------*/
bool TakuzuState::lost() const {
    //the state is lost if a rule is violated (then it loses)

    //check lines
    for(auto i=0;i<4;i++){
        auto nb_0=0,nb_1=0;
        for(auto j=0;j<4;j++){
            if (board[i][j]=='0')
                nb_0++;
            else if (board[i][j]=='1')
                nb_1++;
        }
        if (nb_0>2 || nb_1>2)
            return true;
    }
    //check columns
    for(auto i=0;i<4;i++){
        auto nb_0=0,nb_1=0;
        for(auto j=0;j<4;j++){
            if (board[j][i]=='0')
                nb_0++;
            else if (board[j][i]=='1')
                nb_1++;
        }
        if (nb_0>2 || nb_1>2)
            return true;
    }
    return false;
}
/*---------------------------------------------------------------------------*/
bool TakuzuState::win() const {
    //the state is lost if a rule is violated (then it loses)

    //check lines
    for(auto i=0;i<4;i++){
        auto nb_0=0,nb_1=0;
        for(auto j=0;j<4;j++){
            if (board[i][j]=='0')
                nb_0++;
            else if (board[i][j]=='1')
                nb_1++;
        }
        if (nb_0!=2 || nb_1!=2)
            return false;
    }
    //check columns
    for(auto i=0;i<4;i++){
        auto nb_0=0,nb_1=0;
        for(auto j=0;j<4;j++){
            if (board[j][i]=='0')
                nb_0++;
            else if (board[j][i]=='1')
                nb_1++;
        }
        if (nb_0!=2 || nb_1!=2)
            return false;

    }
    return true;
}
/*---------------------------------------------------------------------------*/
bool TakuzuState::is_terminal() const {
    //the state is terminal if
    // 1. all the spaces are filled without breaking rules (in this case, it wins)
    // 2. a rule is violated (then it loses)
    return lost() || win();
}
/*---------------------------------------------------------------------------*/
double TakuzuRewardFunction::evaluate(const IState *AState) const {
    if(dynamic_cast<const TakuzuState*>(AState)->win())
        return 1;
    else if(dynamic_cast<const TakuzuState*>(AState)->lost())
        return -1;
    return 0;
}
/*---------------------------------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const TakuzuAction& TA){
    os<<"("<<TA.i<<"-"<<TA.j<<":"<<TA.value<<")";
    return os;
}
/*---------------------------------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const TakuzuState& TS){
    for(auto i=0;i<4;i++){
        for(auto j=0;j<4;j++){
            os<<" "<< TS.board[i][j]<<" ";
        }
        os<<std::endl;
    }
    return os;
}
/*---------------------------------------------------------------------------*/
