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

    bool is_terminal() const override;

    bool  win() const override;

    std::string write(const std::string& AFileName,
               const int AStageIndex,
               const int ANodeId,
               const int ADepth) const override;

    bool  lost() const;

    friend std::ostream& operator<<(std::ostream& os, const TakuzuState& TS);
};

/*---------------------------------------------------------------------------*/
#endif //SPAM_TAKUZU_STATE_H
/*---------------------------------------------------------------------------*/
