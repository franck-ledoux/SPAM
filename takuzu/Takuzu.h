/*---------------------------------------------------------------------------*/
#ifndef MATCHING_TAKUZU_H
#define MATCHING_TAKUZU_H
/*---------------------------------------------------------------------------*/
#include <mcts/IState.h>
#include <mcts/IAction.h>
#include <mcts/IRewardFunction.h>
#include <iostream>
/*---------------------------------------------------------------------------*/
class TakuzuAction : public IAction {
public:
    const int i;
    const int j;
    const char value;

    TakuzuAction(const int AI, const int AJ, const char AVal)
    :i(AI),j(AJ),value(AVal){;};

    bool operator==(const IAction& other) const override {
        const auto &o = (const TakuzuAction &) other;
        return i == o.i && j == o.j && value == o.value;
    }
    friend std::ostream& operator<<(std::ostream& os, const TakuzuAction& TA);

};
/*---------------------------------------------------------------------------*/
class TakuzuState : public IState {
public:
    char board[4][4];

    TakuzuState();
    TakuzuState(const TakuzuState& AState);

    std::vector<IAction*> get_actions() const override;

    /**@brief Computes the state reach from the current one when applying @p AAction
     * @param AAction the action to apply
     * @return the state that is built from this one when applying @p AAction
     */
    const IState* apply(const IAction* AAction) const override;

    bool is_terminal() const override;
    bool  lost() const;
    bool  win() const;

    friend std::ostream& operator<<(std::ostream& os, const TakuzuState& TS);
};

/*---------------------------------------------------------------------------*/
struct TakuzuRewardFunction: public IRewardFunction{


    double evaluate(const IState* AState) const override;

};
/*---------------------------------------------------------------------------*/
#endif //MATCHING_TAKUZU_H
/*---------------------------------------------------------------------------*/
