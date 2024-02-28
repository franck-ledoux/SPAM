/*---------------------------------------------------------------------------*/
#include <iostream>
#include "../inc/TakuzuAction.h"
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
