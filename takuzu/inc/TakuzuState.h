/*---------------------------------------------------------------------------*/
#ifndef SPAM_TAKUZU_STATE_H
#define SPAM_TAKUZU_STATE_H
/*---------------------------------------------------------------------------*/
#include "mcts/IState.h"
#include <iostream>
#include <memory>
/*---------------------------------------------------------------------------*/
class TakuzuState : public IState {
public:
    char board[4][4];

    TakuzuState();
    TakuzuState(const TakuzuState& AState);

    std::vector<std::shared_ptr<IAction>> get_actions() const override;

    /**@brief Computes the state reach from the current one when applying @p AAction
     * @param AAction the action to apply
     * @return the state that is built from this one when applying @p AAction
     */
    std::shared_ptr<IState> apply(std::shared_ptr<IAction>  AAction) const override;

    bool is_terminal() const override;

    bool  win() const override;

    void write(const std::string& AFileName,
               const int AStageIndex,
               const int ANodeId,
               const int ADepth) const override;
    bool  lost() const;

    friend std::ostream& operator<<(std::ostream& os, const TakuzuState& TS);
};

/*---------------------------------------------------------------------------*/
#endif //SPAM_TAKUZU_STATE_H
/*---------------------------------------------------------------------------*/
