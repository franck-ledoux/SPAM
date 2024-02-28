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

    bool operator==(const IAction& other) const override;

    friend std::ostream& operator<<(std::ostream& os, const TakuzuAction& TA);

};
/*---------------------------------------------------------------------------*/
#endif //SPAM_TAKUZU_ACTION_H
/*---------------------------------------------------------------------------*/
